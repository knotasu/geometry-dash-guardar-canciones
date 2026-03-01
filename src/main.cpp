#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <filesystem>

using namespace geode::prelude;


std::string rutaCarpetaMusica = "";


std::string obtenerRutaCarpetaMusica() {
    std::string rutaBase;
    
    #if defined(GEODE_IS_ANDROID)
        
        
           
            rutasBase.push_back(geode::dirs::getSaveDir().string());
            rutasBase.push_back("/data/data/" + std::string(geode::utils::game::getPackageName()) + "/files/");
        
        
    #elif defined(GEODE_IS_IOS)
        
        rutaBase = "/var/mobile/Containers/Data/Application/GeometryDash/Documents/";
        
    #elif defined(GEODE_IS_WINDOWS)
        
        const char* userProfile = getenv("USERPROFILE");
        if (userProfile) {
            rutaBase = std::string(userProfile) + "\\Documents\\";
        } else {
            // Fallback
            rutaBase = "C:\\Users\\Default\\Documents\\";
        }
        
    #elif defined(GEODE_IS_MACOS)
        // macOS: ~/Documents (Case Sensitive)
        const char* home = getenv("HOME");
        if (home) {
            // Verificar si está usando iCloud
            std::string iCloudPath = std::string(home) + "/Library/Mobile Documents/com~apple~CloudDocs/Documents/";
            if (std::filesystem::exists(iCloudPath)) {
                rutaBase = iCloudPath;
            } else {
                // Ruta estándar de macOS
                rutaBase = std::string(home) + "/Documents/";
            }
        } else {
            rutaBase = "/Users/Shared/Documents/";
        }
        
    #else
        // LINUX: ~/Música (o ~/Music si no existe)
        const char* home = getenv("HOME");
        if (home) {
            // Intentar con "Música" (español)
            rutaBase = std::string(home) + "/Música/";
            
            // Si no existe, intentar con "Music" (inglés)
            if (!std::filesystem::exists(rutaBase)) {
                rutaBase = std::string(home) + "/Music/";
            }
            
            // Si ninguna existe, crear en Música (español)
            std::error_code ec;
            std::filesystem::create_directories(rutaBase, ec);
        } else {
            rutaBase = "/tmp/";
        }
    #endif
    
    // Añadimos el nombre de nuestra carpeta
    std::string rutaCompleta = rutaBase + "MUSICA KNOTASU MOD/";
    
    return rutaCompleta;
}

// Función para asegurar que la carpeta existe
bool crearCarpetaSiNoExiste(const std::string& ruta) {
    std::error_code ec;
    if (!std::filesystem::exists(ruta)) {
        if (std::filesystem::create_directories(ruta, ec)) {
            log::info("Carpeta creada: {}", ruta);
            return true;
        } else {
            log::error("Error al crear carpeta {}: {}", ruta, ec.message());
            return false;
        }
    }
    return true;
}

class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelInfoLayer::init(level, p1)) return false;

        // Configurar la carpeta automáticamente al iniciar
        if (rutaCarpetaMusica.empty()) {
            rutaCarpetaMusica = obtenerRutaCarpetaMusica();
            crearCarpetaSiNoExiste(rutaCarpetaMusica);
        }

        // 1. Crear el diseño de tu botón
        auto spriteBoton = CCSprite::create("boton_knotasu.png"_spr);
        
        // 👉 AQUÍ LE CAMBIAS EL TAMAÑO AL BOTÓN 👈
        // 1.0f es normal. 0.8f es más pequeño. 1.2f es más grande.
        spriteBoton->setScale(0.3f); 
        
        // 2. Crear el botón interactivo
        auto miBoton = CCMenuItemSpriteExtra::create(
            spriteBoton,
            this,
            menu_selector(MyLevelInfoLayer::alTocarGuardar)
        );

        // 3. Crear el menú que contendrá el botón
        auto miMenu = CCMenu::create();
        
        // 4. ANCLAR EL BOTÓN (Para que se quede quieto)
        auto winSize = CCDirector::get()->getWinSize(); 
        
        // 👉 AQUÍ CAMBIAS LA POSICIÓN DEL BOTÓN 👈
        // Cambia el "40" de la izquierda para moverlo a los lados.
        // Cambia el "40" de la derecha para moverlo arriba/abajo.
        miMenu->setPosition({winSize.width - 120, 40}); 
        
        miBoton->setPosition({0, 0}); // (Este déjalo así en 0, 0)

        miMenu->addChild(miBoton);
        addChild(miMenu);

        return true;
    }
    
   


    void alTocarGuardar(CCObject*) {
        // Verificar que la carpeta existe
        if (!crearCarpetaSiNoExiste(rutaCarpetaMusica)) {
            FLAlertLayer::create(
                "Error",
                "No se pudo crear la carpeta MUSICA KNOTASU MOD",
                "OK"
            )->show();
            return;
        }

        auto level = m_level;
        int songID = level->m_songID;
        
        if (songID == 0) {
            FLAlertLayer::create(
                "Info", 
                "Este nivel no tiene canción personalizada", 
                "OK"
            )->show();
            return;
        }

        // Buscar la canción en diferentes ubicaciones según plataforma
        std::vector<std::string> rutasBase;
        
        #if defined(GEODE_IS_ANDROID)
            // Android - Múltiples ubicaciones posibles
            rutasBase.push_back("/data/data/com.robtop.geometryjazz/files/");
            rutasBase.push_back("/storage/emulated/0/Android/data/com.robtop.geometryjazz/files/");
            rutasBase.push_back("/storage/emulated/0/");
            
        #elif defined(GEODE_IS_IOS)
            // iOS
            rutasBase.push_back("/var/mobile/Containers/Data/Application/GeometryDash/Documents/");
            rutasBase.push_back("/var/mobile/Containers/Data/Application/GeometryDash/Library/");
            
        #elif defined(GEODE_IS_WINDOWS)
            // Windows - Steam y versiones normales
            const char* localAppData = getenv("LOCALAPPDATA");
            if (localAppData) {
                rutasBase.push_back(std::string(localAppData) + "\\GeometryDash\\");
            }
            rutasBase.push_back("C:\\Users\\Default\\AppData\\Local\\GeometryDash\\");
            
            // Para Steam en Windows
            const char* programFiles = getenv("PROGRAMFILES");
            if (programFiles) {
                rutasBase.push_back(std::string(programFiles) + "\\Steam\\steamapps\\common\\GeometryDash\\");
            }
            
        #elif defined(GEODE_IS_MACOS)
            // macOS
            const char* home = getenv("HOME");
            if (home) {
                rutasBase.push_back(std::string(home) + "/Library/Application Support/GeometryDash/");
                rutasBase.push_back(std::string(home) + "/Library/Caches/GeometryDash/");
            }
            
        #else
            // LINUX - Múltiples ubicaciones para Steam/Proton
            const char* home = getenv("HOME");
            if (home) {
                // Steam Flatpak
                rutasBase.push_back(std::string(home) + "/.var/app/com.valvesoftware.Steam/data/Steam/steamapps/compatdata/322170/pfx/drive_c/users/steamuser/AppData/Local/GeometryDash/");
                
                // Steam normal (debian-installation)
                rutasBase.push_back(std::string(home) + "/.steam/debian-installation/steamapps/compatdata/322170/pfx/drive_c/users/steamuser/AppData/Local/GeometryDash/");
                
                // Steam normal (.steam)
                rutasBase.push_back(std::string(home) + "/.steam/steam/steamapps/compatdata/322170/pfx/drive_c/users/steamuser/AppData/Local/GeometryDash/");
                
                // Steam normal (.local/share)
                rutasBase.push_back(std::string(home) + "/.local/share/Steam/steamapps/compatdata/322170/pfx/drive_c/users/steamuser/AppData/Local/GeometryDash/");
                
                // Versión nativa (si existe)
                rutasBase.push_back(std::string(home) + "/.local/share/GeometryDash/");
                rutasBase.push_back(std::string(home) + "/.cache/GeometryDash/");
            }
        #endif
        
        std::string nombreBase = std::to_string(songID);
        bool encontrado = false;
        std::filesystem::path rutaOriginal;
        std::string extension;

        log::info("Buscando canción ID: {} en MUSICA KNOTASU MOD", songID);

        // Buscar el archivo
        for (const auto& rutaBase : rutasBase) {
            auto rutaMp3 = std::filesystem::path(rutaBase) / (nombreBase + ".mp3");
            auto rutaOgg = std::filesystem::path(rutaBase) / (nombreBase + ".ogg");
            
            log::info("Buscando en: {}", rutaMp3.string());
            
            if (std::filesystem::exists(rutaMp3)) {
                rutaOriginal = rutaMp3;
                extension = ".mp3";
                encontrado = true;
                log::info("¡Encontrado MP3!");
                break;
            }
            else if (std::filesystem::exists(rutaOgg)) {
                rutaOriginal = rutaOgg;
                extension = ".ogg";
                encontrado = true;
                log::info("¡Encontrado OGG!");
                break;
            }
        }

        if (encontrado) {
            std::error_code ec;
            
            // Crear nombre de destino en nuestra carpeta
            std::string destino = rutaCarpetaMusica + nombreBase + extension;
            
            log::info("Copiando a: {}", destino);
            
            if (std::filesystem::copy_file(rutaOriginal, destino, 
                                           std::filesystem::copy_options::overwrite_existing, ec)) {
                
                // Mensaje personalizado para cada plataforma
                std::string mensaje;
                std::string rutaAmigable;
                
                #if defined(GEODE_IS_ANDROID)
                    rutaAmigable = "Almacenamiento Interno/Android/data/com.robtop.geometryjazz/files/MUSICA KNOTASU MOD/";
                    mensaje = "¡Canción guardada!\n📱 " + rutaAmigable;
                    
                #elif defined(GEODE_IS_IOS)
                    rutaAmigable = "Documents/MUSICA KNOTASU MOD/";
                    mensaje = "¡Canción guardada!\n🍎 " + rutaAmigable;
                    
                #elif defined(GEODE_IS_WINDOWS)
                    rutaAmigable = "Documentos/MUSICA KNOTASU MOD/";
                    mensaje = "¡Canción guardada!\n🪟 " + rutaAmigable;
                    
                #elif defined(GEODE_IS_MACOS)
                    rutaAmigable = "Documents/MUSICA KNOTASU MOD/";
                    mensaje = "¡Canción guardada!\n💻 " + rutaAmigable;
                    
                #else
                    // LINUX
                    rutaAmigable = "Música/MUSICA KNOTASU MOD/";
                    mensaje = "¡Canción guardada!\n🐧 " + rutaAmigable;
                #endif
                
                mensaje += "\n🎵 " + nombreBase + extension;
                
                FLAlertLayer::create(
                    "KNOTASU SAVER",
                    mensaje.c_str(),
                    "¡BRUTAL!"
                )->show();
                
                log::info("¡Copia exitosa en: {}", destino);
            } else {
                FLAlertLayer::create(
                    "Error",
                    ("Fallo al copiar:\n" + ec.message()).c_str(),
                    "OK"
                )->show();
                
                log::error("Error copiando: {}", ec.message());
            }
        } else {
            std::string mensaje = "No se encontró la canción " + nombreBase + "\n";
            mensaje += "¿La has descargado en el juego?";
            
            FLAlertLayer::create(
                "Aviso",
                mensaje.c_str(),
                "OK"
            )->show();
            
            log::error("Canción no encontrada para ID: {}", songID);
        }
    }
};
