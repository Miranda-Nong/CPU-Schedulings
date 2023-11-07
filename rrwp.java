import java.util.*;

class Process {
    int priority;
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;

    public Process(int processId, int priority, int arrivalTime, int burstTime) {
        this.processId = processId;
        this.priority = priority;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

public class rrwp {
    int processID = 0;
    int time = 1;
    int timeQuantum;

    public static void main(String[] args) {
        rrwp f = new rrwp();
        ArrayList<Process> list = new ArrayList<>();
        f.read(list);
        ArrayList<int[]> gChart = f.produceChart(list);
        f.printTable(list);
        f.printChart(gChart);
    }

    void read(ArrayList<Process> list) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter time quantum");
        timeQuantum = sc.nextInt();
        System.out.println("Enter the number of processes");
        int n = sc.nextInt();
        System.out.println("Enter the process details");
        System.out.println("PId\tPri\tAT\tBT");
        for (int i = 0; i < n; i++) {
            int pId = sc.nextInt();
            int priority = sc.nextInt();
            int at = sc.nextInt();
            int bt = sc.nextInt();
            list.add(new Process(pId, priority, at, bt));
        }
    }

    void addProcess(ArrayList<Process> list, Queue<Process> queue, boolean[] completed, int currTime) {
        int priority = Integer.MAX_VALUE;
        int i = 0;
        for (Process p : list) {
            if (!completed[i] && p.arrivalTime <= currTime && p.priority < priority) {
                priority = p.priority;
            }
            i++;
        }
        queue.clear();
        i = 0;
        for (Process p : list) {
            if (!completed[i] && p.arrivalTime <= currTime && p.priority == priority) {
                queue.add(p);
            }
            i++;
        }
    }

    ArrayList<int[]> produceChart(ArrayList<Process> list) {
        ArrayList<int[]> gChart = new ArrayList<>();
        Queue<Process> queue = new LinkedList<>();
        int[] burst = new int[list.size()];
        boolean[] completed = new boolean[list.size()];
        int n = list.size();
        int currTime = 0;
        int chartIndex = -1;
        while (n > 0) {
            addProcess(list, queue, completed, currTime);
            while (queue.isEmpty())
                addProcess(list, queue, completed, ++currTime);
            int size = queue.size();
            while (size-- > 0) {
                Process p = queue.poll();
                if (chartIndex > -1 && !queue.isEmpty() && gChart.get(chartIndex)[processID] == p.processId)
                    p = queue.poll();
                if (p == null)
                    break;
                int index = list.indexOf(p);
                if (p.burstTime > timeQuantum) {
                    p.burstTime -= timeQuantum;
                    currTime += timeQuantum;
                    burst[index] += timeQuantum;
                } else {
                    currTime += p.burstTime;
                    burst[index] += p.burstTime;
                    p.burstTime = burst[index];
                    completed[index] = true;
                    p.completionTime = currTime;
                    p.turnAroundTime = p.completionTime - p.arrivalTime;
                    p.waitingTime = p.turnAroundTime - p.burstTime;
                    n--;
                }
                gChart.add(new int[] { p.processId, currTime });
                chartIndex++;
            }
        }
        return gChart;
    }

    void printTable(ArrayList<Process> list) {
        float avgWaitingTime = 0;
        float avgTurnAroundTime = 0;
        System.out.println(
                "\nTable:\nProcessID Priority BurstTime ArrivalTime CompletionTime TurnAroundTime WaitingTime");
        for (Process p : list) {
            avgWaitingTime += p.waitingTime;
            avgTurnAroundTime += p.turnAroundTime;
            System.out.printf("%9d ", p.processId);
            System.out.printf("%8d ", p.priority);
            System.out.printf("%9d ", p.burstTime);
            System.out.printf("%11d ", p.arrivalTime);
            System.out.printf("%14d ", p.completionTime);
            System.out.printf("%14d ", p.turnAroundTime);
            System.out.printf("%11d\n", p.waitingTime);
        }
        avgWaitingTime = avgWaitingTime / list.size();
        avgTurnAroundTime = avgTurnAroundTime / list.size();
        System.out.println("\nAverage waiting time is " + avgWaitingTime);
        System.out.println("Average turn around time is " + avgTurnAroundTime);
    }

    void printChart(ArrayList<int[]> gChart) {
        System.out.println("\nGANTT Chart: (P0 - Idle State)");
        System.out.print("Process: |");
        for (int[] process : gChart) {
            System.out.print("  P" + process[processID] + "  |");
        }
        System.out.print("\nTime:    0");
        for (int[] process : gChart) {
            System.out.printf("%s%7d", (process[processID] > 9) ? " " : "", process[time]);
        }
        System.out.println();
    }
}