class ThreadA extends Thread {
    public void run() {
        for (int i = 0; i <= 5; i++) {
            System.out.println("From Thread A with i = " + -1 * i);
        }
        System.out.println("Exiting From Thread A and Thread ID is: " + Thread.currentThread().getId());
    }
}

class ThreadB extends Thread {
    public void run() {
        for (int j = 0; j <= 5; j++) {
            System.out.println("From Thread B with j = " + 2 * j);
        }
        System.out.println("Exiting From Thread B and Thread ID is: " + Thread.currentThread().getId());
    }
}

class ThreadC extends Thread {
    public void run() {
        for (int k = 0; k <= 5; k++) {
            System.out.println("From Thread C with k = " + 2 * k);
        }
        System.out.println("Exiting From Thread C and Thread ID is: " + Thread.currentThread().getId());
    }
}

public class MultiThreadClass
{
    //Run|Debug
    public static void main(String args[])
    {
        ThreadA a=new ThreadA();
        ThreadB b= new ThreadB();
        ThreadC c= new ThreadC();
        a.start();
        b.start();
        c.start();
        //System.out.println("Multithreading is over");
    }
}