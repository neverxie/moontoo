#include "all.h"
#include "gic_pl400.h"

/* 定时器 */
extern void timer_init(void);
extern unsigned int timer_get(void);
extern void timer_clear_pending(void);
int cnt;

/* 串口 */
extern void uart0_init(void);
extern void uart0_clear_tx_pending(void);
extern void uart0_clear_rx_pending(void);
extern void uart1_init(void);
extern void uart1_clear_tx_pending(void);
extern void uart1_clear_rx_pending(void);
extern void writel(unsigned int v, volatile void *addr);
extern unsigned int readl(volatile void *addr);
int u;

void main(void) {
    int i;
    int sum = 0;

    for (i = 1; i <= 100; i++) {
        sum += i;
    }
    printf("1 + 2 + ... + 100 = %d\n", sum);
    printf("hello world!\n");

    initIRQController();
    timer_init();
    maskInterrupt(0, 35);

    uart0_init();
    maskInterrupt(0, 37);

    // 也可以调用汇编使能中断
    //irq_enable();
    { 
        uint32_t cpsr;
        // irq: 0x80
        // fiq: 0x40
        asm volatile ("mrs %0, cpsr\n\tbic %0,#0x80\t\nmsr cpsr_cxfs, %0":"=r"(cpsr));
    }
    while (1) {
        //writel(99, (void *)0x10009000);
    }
}

void irq_handle(void) {
    unsigned int cur;
    interrupt_t cur_irq;

    cur_irq = getActiveIRQ();

    printf("hello irq\n");

    cur = timer_get();

    printf("cur:%d\n", cur);

    if (cur_irq == 35) {
        // !@清除定时器flag
        timer_clear_pending();
        printf("[time init: %d]\n", ++cnt);
        //writel(99, (void *)0x1000a000);
    }
    // !@清除gic，不关，新的中断就不会通知
    //ackInterrupt(cur_irq);
    //while (1);

    if (cur_irq == 37) {
        //uart1_clear_rx_pending();
        //uart1_clear_tx_pending();
        printf("uart1 中断\n");
        printf("不知道接收到啥%c\n", readl((void *)0x10009000));
    }

    ackInterrupt(cur_irq);
}
