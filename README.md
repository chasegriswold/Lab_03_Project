Chase Griswold
Embedded Systems 6780-003
Lab-03 Timers

README

In our recent lab session, we explored the functionality of timers, with a particular focus on utilizing the SysTick timer. The SysTick timer, a basic peripheral component, operates using a 24-bit down-counting register that decreases with every processor clock cycle. When this register hits zero, it triggers an interrupt, serving as a fundamental mechanism for generating a consistent system "tick" or timing reference signal.

We learned that this timing reference signal is essential for indicating the passage of time in our system. In practical terms, the SysTick timer finds application in various contexts, such as within the HAL delay libraries and in the context switcher of real-time operating systems.

We also discussed the significance of accurate timing in embedded systems. While processors execute code in units of clock cycles, accurately measuring time without dedicated hardware timers becomes challenging and inefficient. This need for precision timing arises from the requirements of many embedded systems, which often rely on specific timings or schedules for communication tasks and interactions with the physical world.

At the heart of all timers lies a simple concept: they are essentially registers that increment or decrement in response to trigger signals. This basic functionality enables the generation of hardware interrupts, including those facilitated by the SysTick timer. Throughout the lab, we focused on understanding and utilizing the SysTick timer, recognizing it as the most straightforward among the onboard timer peripherals available to us.