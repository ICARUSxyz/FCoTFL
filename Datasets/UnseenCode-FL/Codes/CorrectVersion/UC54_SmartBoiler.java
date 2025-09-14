package a;

import java.util.*;

class ColdStorage {
    private double maxTemp;
    private double minTemp;
    private double currentTemp;
    private List<String> tempLog;

    public ColdStorage(double maxTemp, double minTemp, double initialTemp) {
        this.maxTemp = maxTemp;
        this.minTemp = minTemp;
        this.currentTemp = initialTemp;
        this.tempLog = new ArrayList<>();
    }

    // 更新存储温度
    public void updateTemperature(double changeAmount) {
        currentTemp += changeAmount;

        String message = String.format("Current Temperature: %.1f°C", currentTemp);
        if (currentTemp > maxTemp) {
            message += " | WARNING: Over-temperature Detected! Risk of Spoilage.";
        } else if (currentTemp < minTemp) {
            message += " | ALERT: Freezing Risk! Possible Product Damage.";
        }

        System.out.println(message);
        tempLog.add(message);
    }

    // 显示温度日志
    public void printTempLog() {
        System.out.println("\nCold Storage Temperature Log:");
        for (String log : tempLog) {
            System.out.println(log);
        }
    }
}

public class c109_SmartBoiler {
    public static void main(String[] args) {
        ColdStorage storage = new ColdStorage(8.0, 2.0, 5.0); // 最大 8°C，最小 2°C，初始 5°C

        // 测试用例
        storage.updateTemperature(2.0);  // 增加至 7°C（正常）
        storage.updateTemperature(-4.0); // 降至 3°C（正常）
        storage.updateTemperature(-2.0); // 降至 1°C（低温警报）
        storage.updateTemperature(4.0);  // 增至 5°C（正常）
        storage.updateTemperature(5.0);  // 增至 10°C（超温警报）
        storage.printTempLog(); // 显示温度日志
    }
}	