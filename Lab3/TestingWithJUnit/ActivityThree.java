package TestingWithJUnit;

class PiThread extends Thread {
    private final int sizeThreads;
    private final int idThreads;
    private final int n;
    private double sum  = 0;

    public PiThread(int sizeThreads, int idThreads, int N) {
        this.sizeThreads = sizeThreads;
        this.idThreads = idThreads;
        this.n = N;
    }


    @Override
    public void run() {
        for (int i = 0; i <= n; i++) {
            if (i % sizeThreads == idThreads) {
                sum += Math.pow(-1, i) / (2 * i + 1);
            }
        }
    }

    public double getSum() {
        return sum;
    }
}

public class ActivityThree {

    static int sizeThreads;
    static int n;

    public ActivityThree(int sizeThreads, int n){
        this.sizeThreads = sizeThreads;
        this.n = n;
    }

    public static void main (String [] args) throws InterruptedException {
        double marginOfError;

        n = 50;
        sizeThreads = 2;

        marginOfError = Math.PI - getPi();

        System.out.println("First Test (Threads = 2 and N = 50" + marginOfError);

        n = 100;
        sizeThreads = 4;

        marginOfError = Math.PI - getPi();

        System.out.println("Second Test (Threads = 4 and N = 100" + marginOfError);

        n = 1000;
        sizeThreads = 4;

        marginOfError = Math.PI - getPi();

        System.out.println("Third Test (Threads = 4 and N = 1000" + marginOfError);

        n = 10000;
        sizeThreads = 4;

        marginOfError = Math.PI - getPi();

        System.out.println("Fourth Test (Threads = 4 and N = 10000" + marginOfError);

        n = 100000;
        sizeThreads = 4;

        marginOfError = Math.PI - getPi();

        System.out.println("Fifth Test (Threads = 4 and N = 100000" + marginOfError);
    }

    public static double getPi() throws InterruptedException {
        double value = 0;

        PiThread[] threads = new PiThread[sizeThreads];

        for (int i = 0; i < sizeThreads; i++) {
            threads[i] = new PiThread(sizeThreads, i, n);
            threads[i].start();
        }
        for (int i = 0; i < sizeThreads; i++) {
            threads[i].join();
        }

        for (int i = 0; i < sizeThreads; i++) {
            value += threads[i].getSum();
        }

        double pi = 4 * value;

        return pi;
    }
}
