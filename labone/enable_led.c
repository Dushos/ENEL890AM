void driver_Open(void)
{
    // Enable clock for GPIOA peripheral
    RCC->APB2ENR |= (1 << 2);

    // Set Pin 5 as an output and enable it
    uint32_t reg = *((uint32_t *) GPIOA_CRL);
    reg &= ~(0xF << 20);
    reg |= (0x1 << 20);
    *((uint32_t *) GPIOA_CRL) = reg;

    // Enable the LED2 connected to Pin 5
    *((uint32_t *) GPIOA_BSRR) = (1 << 5);
}