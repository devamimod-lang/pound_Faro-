# Mapeo Horizon FS → SVC para Pound

## Servicios de FS en Citron
Ruta: `citron/src/core/hle/service/filesystem/`

* `fsp/fs_i_file.cpp` – operaciones de archivo: OpenFile, ReadFile, WriteFile, CloseFile, FlushData, etc.
* `fsp/fs_i_directory.cpp` – OpenDirectory, ReadDirectory, CloseDirectory
* `fsp/fs_i_storage.cpp` – Storage, mount/unmount
* `filesystem/filesystem.cpp` – servicio principal `fs:USER` y `fs:DEVICE`

## Correspondencia con SVC kernel
Los servicios FS se comunican con kernel vía IPC y SVCs:
* `SVC_MAPMEMORY 0x4` / `SVC_UNMAPMEMORY 0x5` – mapear buffers para IPC
* `SVC_CREATEEVENT 0x45` – sincronización
* `SVC_READWRITEREGISTER 0x4E` – acceso a registros
* IPC via `SVC_SENDSYNCREQUEST 0x21`, `SVC_REPLYANDRECEIVE 0x43`

## Mapeo propuesto para Pound
### FS virtual básico
Implementado en `src/core/hle/fs_virtual.h/.c`
* `fs_open` → crea handle virtual
* `fs_read` → stub retorna 0
* `fs_write` → acepta datos
* `fs_close` → libera handle

### Integración SVC
En `src/core/hle/syscalls.c` mapear:
* SVC_CREATEEVENT → crear evento de sincronización
* SVC_MAPMEMORY → mapear buffer IPC para transferencia FS

### Próximos pasos
1. Implementar `fs:USER` service stub que responda OpenFile/ReadFile/WriteFile con fs_virtual
2. Añadir mapeo de rutas virtuales: `save:/`, `rom:/`, `sdmc:/`
3. Integrar con NAND virtual en `/tmp/pound_fs/`
4. Añadir respuestas IPC para `IFileSystem::OpenFile` y `IFile::Read`/`Write`

## Código de referencia Citron
* `citron/src/core/hle/service/filesystem/fsp/fs_i_file.cpp`
* `citron/src/core/hle/service/filesystem/fsp/fsp_srv.cpp`
* `citron/src/core/hle/service/filesystem/filesystem.cpp`

Licencia GPL-3.0: No copiar código, reutilizar diseño de interfaz y nombres de métodos.
