class PiThread extends Thread {
    private final int sizeThreads;
    private final int idThreads;
    private final int n;
    private double sum  = 0;

    public PiThread(int sizeThreads, int idThreads, int n) {
        this.sizeThreads = sizeThreads;
        this.idThreads = idThreads;
        this.n = n;
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

public class MainCode {

    public static void main (String [] args) throws InterruptedException {
        int sizeThreads;
        double n;
        double value = 0;

        for (int i = 0; i < 5; i++){
            value = 0;
            sizeThreads = i + 1;
            n = Math.pow(100, i + 1);

            System.out.println("Starting test with " + sizeThreads + " Threads and N equal to " + n);

            PiThread[] threads = new PiThread[sizeThreads];

            for (i = 0; i < sizeThreads; i++) {
                threads[i] = new PiThread(sizeThreads, i, (int) n);
                threads[i].start();
            }
            for (i = 0; i < sizeThreads; i++) {
                threads[i].join();
            }

            for (i = 0; i < sizeThreads; i++) {
                value += threads[i].getSum();
            }

            System.out.println(value);

            double pi = 4 * value;
            double marginOfError = pi - Math.PI;

            System.out.println("Value of Pi: "+ pi);
            System.out.println("Margin of error: " + marginOfError);
            System.out.println("End of Test\n\n");
        }
    }
}
