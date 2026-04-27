/*
 * Project: Temperature Control System
 * Device: PIC18F4550
 * Setup: Internal Oscillator or 20MHz Crystal
 */

#include <xc.h>
#include <stdio.h>

// --- 1. CONFIGURATION BITS ---
// These tell the chip how to start up.
#pragma config PLLDIV = 5       // Divide by 5 (20MHz input)
#pragma config CPUDIV = OSC1_PLL2 
#pragma config FOSC = HS        // High Speed Crystal Oscillator
#pragma config WDT = OFF        // Watchdog Timer OFF (Prevents random resets)
#pragma config PBADEN = OFF     // IMPORTANT: Makes PORTB Digital (fixes LCD issues)
#pragma config LVP = OFF        // Low Voltage Programming OFF
#pragma config BOR = OFF        // Brown Out Reset OFF

#define _XTAL_FREQ 20000000     // Tell compiler we are using 20MHz

// --- 2. PIN DEFINITIONS ---
#define RS LATDbits.LATD0
#define EN LATDbits.LATD1
#define D4 LATDbits.LATD2
#define D5 LATDbits.LATD3
#define D6 LATDbits.LATD4
#define D7 LATDbits.LATD5

#define FAN     LATCbits.LATC0
#define HEATER  LATCbits.LATC1

// --- 3. LCD FUNCTIONS ---
void LCD_Cmd(char cmd) {
    RS = 0; // Command Mode
    
    // Send Upper Nibble (First 4 bits)
    if(cmd & 0x10) D4=1; else D4=0;
    if(cmd & 0x20) D5=1; else D5=0;
    if(cmd & 0x40) D6=1; else D6=0;
    if(cmd & 0x80) D7=1; else D7=0;
    EN = 1; __delay_us(40); EN = 0;

    // Send Lower Nibble (Next 4 bits)
    if(cmd & 0x01) D4=1; else D4=0;
    if(cmd & 0x02) D5=1; else D5=0;
    if(cmd & 0x04) D6=1; else D6=0;
    if(cmd & 0x08) D7=1; else D7=0;
    EN = 1; __delay_us(40); EN = 0;
    
    __delay_ms(2);
}

void LCD_Char(char data) {
    RS = 1; // Data Mode
    
    // Send Upper Nibble
    if(data & 0x10) D4=1; else D4=0;
    if(data & 0x20) D5=1; else D5=0;
    if(data & 0x40) D6=1; else D6=0;
    if(data & 0x80) D7=1; else D7=0;
    EN = 1; __delay_us(40); EN = 0;

    // Send Lower Nibble
    if(data & 0x01) D4=1; else D4=0;
    if(data & 0x02) D5=1; else D5=0;
    if(data & 0x04) D6=1; else D6=0;
    if(data & 0x08) D7=1; else D7=0;
    EN = 1; __delay_us(40); EN = 0;
    
    __delay_us(50);
}

void LCD_Init() {
    TRISD = 0x00; // Make PORTD Output
    __delay_ms(100);
    // Reset sequence for 4-bit mode
    LCD_Cmd(0x03); __delay_ms(5);
    LCD_Cmd(0x03); __delay_ms(1);
    LCD_Cmd(0x03); 
    LCD_Cmd(0x02); // Enable 4-bit mode
    
    LCD_Cmd(0x28); // 4-bit, 2 lines
    LCD_Cmd(0x0C); // Display ON, Cursor OFF
    LCD_Cmd(0x01); // Clear Display
}

void LCD_String(char *str) {
    while(*str) LCD_Char(*str++);
}

void LCD_Set_Cursor(char row, char col) {
    if(row == 1) LCD_Cmd(0x80 + col - 1);
    else LCD_Cmd(0xC0 + col - 1);
}

// --- 4. ADC (SENSOR) FUNCTIONS ---
void ADC_Init() {
    TRISAbits.TRISA0 = 1;   // RA0 is Input
    ADCON1 = 0x0E;          // AN0 is Analog, all others Digital
    ADCON0 = 0x01;          // Enable ADC Channel 0
    ADCON2 = 0xB6;          // Right justify, slow clock
}

unsigned int ADC_Read() {
    ADCON0bits.GO = 1;      // Start measuring
    while(ADCON0bits.GO);   // Wait until done
    return ((ADRESH << 8) + ADRESL); // Return result
}

// --- 5. MAIN PROGRAM ---
void main(void) {
    TRISC = 0x00; // Make PORTC Output (Fan/Heater)
    FAN = 0;
    HEATER = 0;
    
    ADC_Init();
    LCD_Init();
    
    int temp_val;
    char buffer[16];
    
    LCD_Set_Cursor(1,1);
    LCD_String("Starting...");
    __delay_ms(1000);
    LCD_Cmd(0x01); // Clear screen
    
    while(1) {
        // Read Sensor
        // Formula: (ADC * 500) / 1023  approx equals Degrees C
        temp_val = (ADC_Read() * 500) / 1023;
        
        // Print to LCD
        sprintf(buffer, "Temp: %d C   ", temp_val);
        LCD_Set_Cursor(1,1);
        LCD_String(buffer);
        
        // Control Fan and Heater
        if(temp_val > 30) {
            FAN = 1;
            HEATER = 0;
            LCD_Set_Cursor(2,1);
            LCD_String("Cooling: ON ");
        }
        else if(temp_val < 30) {
            FAN = 0;
            HEATER = 1;
            LCD_Set_Cursor(2,1);
            LCD_String("Heating: ON ");
        }
        
        __delay_ms(250); // Small delay
    }
}

