
## Descripción del Repositorio

Este repositorio contiene el desarrollo del **microservicio de procesamiento de posiciones y gestión de geocercas (geofencing)** realizado en lenguaje **C++**, como parte del proyecto de tesis titulado *"Construcción de un Prototipo de Arquitectura Modular Basada en Microservicios para la Optimización de Sistemas de Monitoreo GPS"*.

El objetivo principal del microservicio es **procesar datos de posición GPS en tiempo real**, aplicar lógica de decodificación y codificación, y gestionar eventos relacionados con **geocercas (GeoFences)**. Este componente fue desarrollado utilizando **C++** con el fin de explorar una migración desde el sistema monolítico original **Traccar** hacia una arquitectura basada en microservicios (https://github.com/traccar/traccar).

---

## Objetivos del Microservicio

- **Procesamiento eficiente de datos de posición GPS**
- **Gestión de eventos asociados a geocercas (Geofencing)**
- **Explorar una posible migración del sistema monolítico Traccar a una arquitectura modular basada en C++**
- **Servir como base para futuras implementaciones de microservicios similares**

---

## Arquitectura y Tecnologías Utilizadas

- **Lenguaje:** C++
- **Bibliotecas utilizadas:**
  - [Crow.h](https://github.com/ipkn/crow) – Framework web ligero para servidores HTTP
  - [Boost.Asio](https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio.html) – Para operaciones de red y E/S asíncrona
- **Comunicación:** REST API
- **Base de Datos:** MongoDB 
- **Contenerización:** Docker (pendiente de configuración)

---
## Clonar

### Requisitos previos:
- Compilador C++ compatible (GCC o Clang)
- CMake
- Boost.Asio instalado
- MongoDB y librerías de conexión

### Pasos:

1. Clona el repositorio:
   ```bash
   git clone https://github.com/MrT-coder/POSITION_GEOFENCE_C-.git
   ```

2. Navega al directorio:
   ```bash
   cd POSITION_GEOFENCE_C-
   ```

3. Crea el directorio de compilación y compila:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
---

## Referencia al Proyecto Principal

Este repositorio forma parte de un conjunto más amplio de microservicios desarrollados durante la tesis mencionada. Otros repositorios relacionados:

- [Microservicio de Eventos en Java](https://github.com/MrT-coder/TRACCAR_EVENTS_JAVA)
- [Microservicio de Posición en Java](https://github.com/MrT-coder/TRACCAR_POSITION-GEOFENCE_JAVA)

---
## Estado del Proyecto

Este proyecto se encuentra en estado **experimental y básico**, aún con fallos y sin funcionalidad fija, desarrollado principalmente como parte de una investigación académica. Es útil como punto de partida para proyectos futuros relacionados con sistemas de monitoreo GPS basados en microservicios.

---

## Contribución

Si deseas contribuir al proyecto, siéntete libre de abrir un *issue* o enviar un *pull request*. ¡Cualquier ayuda es bienvenida!

---
