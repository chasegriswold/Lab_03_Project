Chase Griswold
Embedded Systems 6780-003
Lab-03 Timers

README


In this lab, our objective is to get comfortable with using timer interrupts on the STM32F072 Discovery board. We'll be working through a series of exercises, each focusing on different aspects of timer configuration and usage.

First up, we're going to set up Timer 2 (TIM2) to trigger an interrupt at a specific frequency of 4 Hz. This involves configuring the timer registers carefully to achieve the desired interrupt frequency. Once that's done, we'll toggle between the green and orange LEDs in the interrupt handler to visually confirm our setup.

Next, we'll move on to configuring Timer 3 (TIM3) channels for PWM (Pulse Width Modulation). This will allow us to control the brightness of LEDs by changing the duty cycle of the PWM signal. We'll set up channels 1 and 2 of TIM3 for PWM mode and adjust the duty cycle using Capture/Compare Registers.

Then, we'll configure the remaining LEDs (red and blue) on the Discovery board to use alternate function mode, linking them to timer capture/compare channels. This will enable us to control their brightness using PWM, similar to what we did with the other LEDs.

Finally, we'll delve into measuring the PWM output by experimenting with different Capture/Compare Register values for both PWM modes. We'll use a logic analyzer to observe how changing these values affects the duty cycle of the PWM signal and thus the brightness of the LEDs.

By the end of this lab, we should have a solid understanding of timer configuration, interrupts, and PWM output, which are fundamental concepts in microcontroller programming. Let's dive in and get started!




{Information about the last lab: In our recent lab session, we explored the functionality of timers, with a particular focus on utilizing the SysTick timer. The SysTick timer, a basic peripheral component, operates using a 24-bit down-counting register that decreases with every processor clock cycle. When this register hits zero, it triggers an interrupt, serving as a fundamental mechanism for generating a consistent system "tick" or timing reference signal.

We learned that this timing reference signal is essential for indicating the passage of time in our system. In practical terms, the SysTick timer finds application in various contexts, such as within the HAL delay libraries and in the context switcher of real-time operating systems.

We also discussed the significance of accurate timing in embedded systems. While processors execute code in units of clock cycles, accurately measuring time without dedicated hardware timers becomes challenging and inefficient. This need for precision timing arises from the requirements of many embedded systems, which often rely on specific timings or schedules for communication tasks and interactions with the physical world.

At the heart of all timers lies a simple concept: they are essentially registers that increment or decrement in response to trigger signals. This basic functionality enables the generation of hardware interrupts, including those facilitated by the SysTick timer. Throughout the lab, we focused on understanding and utilizing the SysTick timer, recognizing it as the most straightforward among the onboard timer peripherals available to us.}