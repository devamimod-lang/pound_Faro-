# Switch 2 Backward Compatibility & Emulación Interna

## Resumen oficial
* Nintendo Switch 2 usa SoC Nvidia Tegra T239 “Drake” con CPU Cortex-A78C y GPU Ampere SM86.
* Backward compatibility con Switch 1 es parte clave del diseño.
* Implementación es **híbrida software + hardware**:
  * Partes del hardware T239 están mapeadas para emular Tegra X1.
  * OS Horizon en Switch 2 incluye capa de traducción de syscalls y NVN Maxwell → Ampere.
  * Evita emulación 100% software para mantener rendimiento.

Fuentes: Wikipedia Switch 2 / Development, Nintendo statements.

## Qué significa para Pound + Ballistic
* Validar estrategia actual: JIT Ballistic para ARM64 + traducción NVN es consistente con lo que hace Switch 2 internamente.
* Se puede reusar trabajo de Citron:
  * Parsers NRO / NCA
  * HLE Horizon syscalls completas: SVC, FS, FS-Mii, NVN
  * Gestor de memoria y mapeo de regiones
  * Traductor NVN → Vulkan ya productivo en Citron

## Qué ya tiene Citron resuelto
* `src/core/hle/kernel/svc/`: ~30 SVC implementadas
  * svc_thread.cpp, svc_memory.cpp, svc_process_memory.cpp, svc_process.cpp
  * svc_physical_memory.cpp, svc_query_memory.cpp, svc_code_memory.cpp
  * svc_ipc.cpp, svc_session.cpp, svc_port.cpp, svc_event.cpp, svc_condition_variable.cpp
  * svc_light_ipc.cpp, svc_synchronization.cpp, svc_lock.cpp
  * svc_transfer_memory.cpp, svc_shared_memory.cpp
  * svc_power_management.cpp, svc_info.cpp, svc_tick.cpp, svc_processor.cpp
  * svc_cache.cpp, svc_interrupt_event.cpp
* FS HLE en `src/core/hle/service/`
* NVN: `src/video_core/renderer_vulkan/` y `src/video_core/.../nvn`
* NRO loader en `src/core/loader/`

## Propuesta de aprovechamiento
1. **Syscalls Horizon**
   * Extraer tabla SVC de Citron `src/core/hle/kernel/svc_types.h` e `svc_results.h`
   * Migrar stubs a Pound `src/core/hle/syscalls.c` con IDs reales
   * Priorizar: svcMapMemory, svcCreateThread, svcStartThread, svcExitThread, svcOpenFile, svcReadFile, svcWriteFile, svcCloseFile, svcOutputDisplay

2. **NVN Maxwell → Ampere**
   * Reusar mapeo de MMIO de Citron para Tegra X1
   * Extender a SM86: añadir offsets nuevos documentados en NVN_MMIO_MAP.md
   * Traductor SM86 → SPIR-V puede partir de pipeline Vulkan de Citron

3. **NRO / NCA**
   * Adaptar parser de Citron para cargar NROs Switch 1 y detectar modo Switch 2 Update
   * Usar decoder validator actual para comprobar bloques ARM64 antes de JIT

4. **Retrocompat híbrida**
   * Implementar flag `switch1_compat_mode` en `pound_switch2_t`
   * En modo compat: mapear MMIO Tegra X1 a T239, limitar features GPU
   * En modo nativo: habilitar SM86 completo y NVN extendido

## Riesgos
* Citron está licenciado GPL-3.0 con requerimiento de compartir modificaciones. Reutilizar código directamente implica licencia compatible. Mejor opción: reutilizar diseños, tablas y lógica de mapeo, reimplementar stubs en Pound.
* No hay dumps de firmware Switch 2 confirmando offsets exactos. Basar mapeo en hipótesis de Switch 1.

## Próximos pasos concretos
* Generar tabla unificada SVC ID → nombre usando Citron como referencia
* Integrar FS virtual con mapeo a directorio NAND en `src/core/hle/svc_files.c`
* Conectar NVN command buffer a creación de pipeline Vulkan real en `vk_backend.c`
* Añadir test de compatibilidad Switch 1 NRO que ejecute `svcOutputDisplay` + dibujo básico

