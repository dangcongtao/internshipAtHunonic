#include <stdio.h>
#include "cJSON.h"

int main () {

    const char* PAYLOADS[] = {
        "{\"wswitch2v\":0, \"action\":1, \"u\":13393,\"name\":\"name1\" }",
        "{\"wswitch2v\":0, \"action\":3, \"u\":13393,\"name\":\"name2\" }",
        "{\"wswitch2v\":0, \"action\":5, \"u\":13393,\"name\":\"name3\" }",
        "{\"wswitch2v\":0, \"action\":7, \"u\":13393,\"name\":\"name4\" }",

        "{\"wswitch2v\":0, \"action\":2, \"u\":13393,\"name\":\"name5\" }",
        "{\"wswitch2v\":0, \"action\":4, \"u\":13393,\"name\":\"name6\" }",
        "{\"wswitch2v\":0, \"action\":6, \"u\":13393,\"name\":\"name7\" }",
        "{\"wswitch2v\":0, \"action\":8, \"u\":13393,\"name\":\"name8\" }",
        NULL
    };

    int index = 0;

    while (PAYLOADS[index] != NULL ) {
        printf ("index = %d \t%s\n", index, PAYLOADS[index]);
    
        cJSON *jsRoot = cJSON_Parse(PAYLOADS[index]);
        if (!jsRoot)
            return 0;

        /* parser */
         cJSON *jsCmd = cJSON_GetObjectItem(jsRoot, "wswitch2v");
        if (jsCmd == NULL) {
            printf("Get JSON cmd\n");
            cJSON_Delete(jsRoot);
            return 0;
        }



        cJSON *js_action = cJSON_GetObjectItem(jsRoot, "action");
        if (js_action == NULL) {
            printf("Get JSON action fail\n");
            cJSON_Delete(jsRoot);
            return 0;
        }

        cJSON *js_u = cJSON_GetObjectItem(jsRoot, "u");
        if (js_u == NULL) 
        {
            printf("Get JSON u fail\n");
            cJSON_Delete(jsRoot);
            return 0;
        }

        cJSON *js_name = cJSON_GetObjectItem(jsRoot, "name");
        if (js_name == NULL) 
        {
            printf("Get JSON name fail\n");
            cJSON_Delete(jsRoot);
            return 0;
        }

        printf ("key = %s value =  %d\n",jsCmd->string, jsCmd->valueint);
        printf ("key = %s value =  %d\n",js_action->string, js_action->valueint);
        printf ("key = %s value =  %d\n",js_u->string, js_u->valueint);
        printf ("key = %s value =  %s\n",js_name->string, js_name->valuestring);
        

        /* cJSON_Delete(js_name);
        cJSON_Delete(js_name);
        cJSON_Delete(js_name);
        cJSON_Delete(js_name); */

        index = index + 1;
    }
    
    printf ("end\n");
    return 0;
}