package a;

public class c111_SmartAirPurifier {

    private double normalAQIThreshold;  // 空气质量正常的最大 AQI 阈值
    private double hazardousAQIThreshold; // 极端污染的 AQI 阈值
    private double currentAQI;         // 当前空气质量指数
    private int fanSpeed;              // 风扇转速（0 代表关闭，1 代表正常，2 代表高速）

    // 构造函数：初始化空气质量阈值和风扇转速
    public c111_SmartAirPurifier(double normalAQIThreshold, double hazardousAQIThreshold, double initialAQI) {
        this.normalAQIThreshold = normalAQIThreshold;
        this.hazardousAQIThreshold = hazardousAQIThreshold;
        this.currentAQI = initialAQI;
        this.fanSpeed = 0; // 默认风扇转速为正常
    }

    // 更新空气质量指数，并根据数值条件调整风扇转速
    public void updateAQI(double newAQI) {
        currentAQI = newAQI;
        adjustFanSpeed();
        System.out.printf("Current AQI: %.2f, Fan Speed: %d%n", currentAQI, fanSpeed);
        if (currentAQI > hazardousAQIThreshold) {
            System.out.println("ALERT: Hazardous air quality detected! Take protective measures.");
        } else if (currentAQI > normalAQIThreshold) {
            System.out.println("WARNING: Poor air quality. Increasing fan speed.");
        } else {
            System.out.println("Air quality is good. Operating at normal speed.");
        }
    }

    // 根据当前 AQI 调整风扇转速
    private void adjustFanSpeed() {
        if (currentAQI >= hazardousAQIThreshold) {
            fanSpeed = 0; // 极端污染情况下，风扇高速运行
        } else if (currentAQI > normalAQIThreshold) {
            fanSpeed = 2; // 轻度污染情况下，提高风扇转速
        } else {
            fanSpeed = 1; // 良好空气质量情况下，风扇保持正常速度
        }
    }

    // 获取当前空气质量指数
    public double getCurrentAQI() {
        return currentAQI;
    }

    // 获取当前风扇转速
    public int getFanSpeed() {
        return fanSpeed;
    }

    public static void main(String[] args) {
        // 初始化空气净化器：正常 AQI 阈值 100，极端污染 AQI 阈值 200，初始 AQI 80
    	c111_SmartAirPurifier purifier = new c111_SmartAirPurifier(100.0, 200.0, 90.0);

        // 测试用例
        purifier.updateAQI(90.0);   // 90，空气质量良好，风扇保持正常
        purifier.updateAQI(150.0);  // 150，空气质量较差，提高风扇转速
        purifier.updateAQI(220.0);  // 220，空气极端污染，风扇高速运转并触发警报
    }
}
