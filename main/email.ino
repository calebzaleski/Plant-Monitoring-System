#include "config.h"
#include "wifi.h"

void sendEmail(String subject, String body, String to) {
    Serial.println("📧 Preparing to send email...");
    
    Session_Config config;
    config.server.host_name = "smtp.gmail.com";
    config.server.port = 465;
    config.login.email = EMAIL_USER;
    config.login.password = EMAIL_APP_PASSWORD;
    config.login.user_domain = "";
    config.secure.startTLS = false;
    
    config.time.ntp_server = "pool.ntp.org,time.nist.gov";
    config.time.gmt_offset = -5;
    config.time.day_light_offset = 0;
    
    SMTP_Message message;
    message.sender.name = "Arduino Plant Monitor";
    message.sender.email = EMAIL_USER;
    message.subject = subject.c_str();
    message.addRecipient("Caleb", to.c_str());
    message.text.content = body.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_normal;
    
    Serial.println("📧 Connecting to SMTP server...");
    if (!smtp.connect(&config)) {
        Serial.println("❌ SMTP connection failed!");
        Serial.println("Error: " + smtp.errorReason());
        return;
    }
    
    if (!MailClient.sendMail(&smtp, &message)) {
        Serial.println("❌ Email send failed!");
        Serial.println("Error: " + smtp.errorReason());
    } else {
        Serial.println("✅ Email sent successfully!");
    }
    
    smtp.closeSession();
}

void checkScheduledEmail() {
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;

    const int scheduledHours[] = {7, 13, 18, 19, 21};
    const int scheduledMinutes[] = {0, 0, 0, 0, 0};

    if (minute != lastMinute) {
        emailSentThisMinute = false;
        lastMinute = minute;
    }

    if (emailSentThisMinute) {
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (hour == scheduledHours[i] && minute == scheduledMinutes[i] && !emailSentThisMinute) {
                    emailSentThisMinute = true;
            sendEmail("Scheduled Soil Update", "Scheduled soil reading:\n" + readSoil()+ "Raw value:\n" + String(readASoil()) + readTemp() + readHumidity() + String(wtime), "Caleb.Zaleski@icloud.com");
            break;
        }
    }

    
}


