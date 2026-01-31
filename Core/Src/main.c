#include "main.h"

int main(void)
{
		SystemClock_Config();
		Delay_ms(100);
		GPIO_Init();
		USART1_Init();
		SPI1_Init();
		
		USART1_SendString("\r\n=== ACK 있는 송신기 입니당 ===\r\n");
		
		nRF_Init_TX();
		
		uint8_t tx_data[32] = " 이 글이 뜬다면 송신 성공! ";
		uint8_t ack_data[32];
		uint8_t cnt = 0;
		char msg[64];
		
		while(1) {
				LED_ON();
				
				tx_data[18] = (cnt / 100) + '0';
        tx_data[19] = ((cnt % 100) / 10) + '0';
        tx_data[20] = (cnt % 10) + '0';
        
        memset(ack_data, 0, 32);
        uint8_t res = nRF_TxPacket(tx_data, ack_data);
        
        if (res == 1) {
            sprintf(msg, "송신 성공 (Cnt: %d) / No Data\r\n", cnt);
            USART1_SendString(msg);
        } else if (res == 3) { // ACK Payload 수신
            USART1_SendString("송신 성공 & 수신 답장: ");
            USART1_SendString((char*)ack_data);
            USART1_SendString("\r\n");
        } else if (res == 2) {
            USART1_SendString("송신 실패: No ACK\r\n");
        } else {
            USART1_SendString("송신 실패: Error\r\n");
        }
        
        LED_OFF();
        cnt++;
        if(cnt > 250) cnt = 0;
        
        Delay_ms(1000);
    }
 }