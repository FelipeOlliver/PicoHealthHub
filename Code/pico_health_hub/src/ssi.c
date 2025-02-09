/**
  ******************************************************************************
  * @file    ssi.h
  * @author  felipeoliveira
  * @version V1.0.0
  * @date    28-Jan-2025
  * @brief   SSI functions.
  ******************************************************************************
  */

#include "ssi.h"


extern float temperature; // Temperatura 
extern int systolicPressure;   // Pressão Sistólica 
extern int diastolicPressure;  // Pressão Diastólica 
extern int spo2Level;       // SpO2 
extern int heartRate;         // Frequência Cardíaca 
// Definições dos nomes das tags SSI
extern const char *tags[] = {
    "temperature", "systolicPressure", "diastolicPressure", "spo2Level", "heartRate"
};
extern int numtags;

// SSI Handler
static const char *ssi_handler(const char *ssi_tag) {
    char buff[32];
    if (strcmp(ssi_tag, "temperature") == 0) {
        snprintf(buff, sizeof(buff), "%.1f", temperature);
        return buff;
    } else if (strcmp(ssi_tag, "systolicPressure") == 0) {
        snprintf(buff, sizeof(buff), "%d", systolicPressure);
        return buff;
    } else if (strcmp(ssi_tag, "diastolicPressure") == 0) {
        snprintf(buff, sizeof(buff), "%d", diastolicPressure);
        return buff;
    } else if (strcmp(ssi_tag, "spo2Level") == 0) {
        snprintf(buff, sizeof(buff), "%d", spo2Level);
        return buff;
    } else if (strcmp(ssi_tag, "heartRate") == 0) {
        snprintf(buff, sizeof(buff), "%d", heartRate);
        return buff;
    }
    return "N/A"; // Se a tag não for reconhecida
}

void ssi_init() {
  http_set_ssi_handler(ssi_handler, tags, numtags);
}