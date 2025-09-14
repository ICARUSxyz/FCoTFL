package a;

public class c100_SmartGasStove {

    private double minFlameIntensity;  // 最低火焰强度阈值
    private double maxFlameIntensity;  // 最高火焰强度阈值
    private double currentFlameIntensity;  // 当前火焰强度
    private double gasFlowRate;  // 当前燃气流量（单位：L/min）

    // 构造函数：初始化火焰强度阈值、初始火焰强度和燃气流量
    public c100_SmartGasStove(double minFlameIntensity, double maxFlameIntensity, double initialFlameIntensity, double initialGasFlowRate) {
        this.minFlameIntensity = minFlameIntensity;
        this.maxFlameIntensity = maxFlameIntensity;
        this.currentFlameIntensity = initialFlameIntensity;
        this.gasFlowRate = initialGasFlowRate;
    }

    // 更新火焰强度，并根据数值条件调整燃气流量
    public void updateFlameIntensity(double newFlameIntensity) {
        currentFlameIntensity = newFlameIntensity;
        adjustGasFlow();
        System.out.printf("Current Flame Intensity: %.2f, Gas Flow Rate: %.2f L/min%n",
                          currentFlameIntensity, gasFlowRate);

        if (currentFlameIntensity < minFlameIntensity) {
            System.out.println("ALERT: Flame intensity too low! Increasing gas flow.");
        } else if (currentFlameIntensity > maxFlameIntensity) {
            System.out.println("ALERT: Flame intensity too high! Decreasing gas flow.");
        } else {
            System.out.println("Flame intensity is optimal. No adjustment needed.");
        }
    }

    // 根据火焰强度调整燃气流量
    private void adjustGasFlow() {
        if (currentFlameIntensity < minFlameIntensity) {
            // 增加燃气流量 20%
            gasFlowRate = gasFlowRate * 1.2;
        } else if (currentFlameIntensity > maxFlameIntensity) {
            // 降低燃气流量 20%
            gasFlowRate = gasFlowRate * 0.8;
        }
        // 当火焰强度在最佳范围内时，不改变燃气流量
    }

    // 获取当前火焰强度
    public double getCurrentFlameIntensity() {
        return currentFlameIntensity;
    }

    // 获取当前燃气流量
    public double getGasFlowRate() {
        return gasFlowRate;
    }

    public static void main(String[] args) {
        // 初始化智能燃气灶系统：最低火焰强度 50，最高火焰强度 80（任意单位），初始火焰强度 70，初始燃气流量 1.0 L/min
    	c100_SmartGasStove stove = new c100_SmartGasStove(50.0, 80.0, 70.0, 1.0);
        
        // 测试用例
        stove.updateFlameIntensity(45.0);  // 低于最低阈值，增加燃气流量
        stove.updateFlameIntensity(85.0);  // 高于最高阈值，降低燃气流量
        stove.updateFlameIntensity(65.0);  // 在最佳范围内，保持燃气流量不变
    }
}
