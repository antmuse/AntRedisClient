#include <stdio.h>
#include "CLogger.h"
#include "HRedisTest.h"


#ifdef   APP_PLATFORM_WINDOWS
#ifdef   APP_DEBUG
#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:console /entry:mainWCRTStartup")
#else       //for release version
#pragma comment(linker, "/subsystem:console /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
//#pragma comment(linker, "/subsystem:windows /entry:mainWCRTStartup")
#endif  //release version

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "ws2_32.lib")
#endif  //APP_PLATFORM_WINDOWS


namespace app {

void AppQuit() {
    //system("PAUSE");
    s8 key = '\0';
    while('*' != key) {
        printf("@Please input [*] to quit");
        scanf("%c", &key);
    }
}

}//namespace app


int main(int argc, char** argv) {
    app::CLogger::getInstance().addReceiver(app::CLogger::ELRT_CONSOLE|
        app::CLogger::ELRT_FILE_HTML);
    app::u32 key = 1;
    while(key) {
        printf("@0 = Exit\n");
        printf("@1 = Redis Pool\n");
        printf("@2 = Redis Cluster\n");
        printf("@3 = Redis Cluster ZSET\n");
        printf("@Input menu id = ");
        scanf("%u", &key);
        switch(key) {
        case 1:
            app::AppTestRedis(1);
            break;
        case 2:
            app::AppTestRedisCluster(1);
            break;
        case 3:
            app::AppTestRedisClusterZset(1);
            break;
        default:break;
        }
        printf("@Task finished\n\n");
    }//while

    printf("@App exit success\n");
    return 0;
}

