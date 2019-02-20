import java.util.Scanner;
import java.lang.management.*;

public class Main {
    public double[] onMult(int size) {
        double[] mat_a = new double[size * size];
        double[] mat_b = new double[size * size];
        double[] mat_c = new double[size * size];

        ThreadMXBean th = ManagementFactory.getThreadMXBean();

        for(int i = 0; i < size * size; ++i) {
            mat_a[i] = 1;
            mat_b[i] = i / size + 1;
            mat_c[i] = 0;
        }

        long id = Thread.currentThread().getId();
        long start = th.getThreadCpuTime(id);

        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j) {
                double temp = 0.0;
                for(int k = 0; k < size; ++k)
                    temp += mat_a[i * size + k] * mat_b[k * size + j];
                mat_c[i * size + j] = temp;
            }

        long end = th.getThreadCpuTime(id);

        for(int i = 0; i < Math.min(10, size); ++i)
            System.out.print(mat_c[i] + " ");
        System.out.println();
        System.out.println("Time: " + (end-start)/1e9);
        
        return mat_c;
    }
    
    public double[] onMultLine(int size) {
        double[] mat_a = new double[size * size];
        double[] mat_b = new double[size * size];
        double[] mat_c = new double[size * size];

        ThreadMXBean th = ManagementFactory.getThreadMXBean();

        for(int i = 0; i < size * size; ++i) {
            mat_a[i] = 1;
            mat_b[i] = i / size + 1;
            mat_c[i] = 0;
        }

        long id = Thread.currentThread().getId();
        long start = th.getThreadCpuTime(id);

        for(int i = 0; i < size; ++i)
            for(int k = 0; k < size; ++k)
                for(int j = 0; j < size; ++j)
                    mat_c[i * size + j] += mat_a[i * size + k] * mat_b[k * size + j];

        long end = th.getThreadCpuTime(id);

        for(int i = 0; i < Math.min(10, size); ++i)
            System.out.print(mat_c[i] + " ");
        System.out.println();
        System.out.println("Time: " + (end-start)/1e9);
        
        return mat_c;
    }

    public static void main(String[] args) {
        Main m = new Main();
        System.out.println("1. Multiplication");
        System.out.println("2. Line Multiplication");
        System.out.println("3. Partitioned Multiplication");

        Scanner reader = new Scanner(System.in);

        while(true) {
            System.out.print("Selection: ");
            int option = reader.nextInt();

            if(option == 0) break;

            System.out.print("Size: ");
            int size = reader.nextInt();

            switch(option) {
                case 1:
                    m.onMult(size);
                    break;
                case 2:
                    m.onMultLine(size);
                    break;
                default:
                    break;
            }
        }
    }
}