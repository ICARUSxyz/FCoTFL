import java.awt.*;
import javax.swing.*;

public class RadarChart extends JPanel {

    private int[] values; // レーダーチャートの値
    private String[] labels; // 各頂点のラベル
    private int maxValue = 70; // 値の最大値（0からこの値までの範囲で指定）

    public RadarChart(int[] values, String[] labels) {
        this.values = values;
        this.labels = labels;
        setPreferredSize(new Dimension(400, 400)); // パネルのサイズを設定
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        int centerX = getWidth() / 2; // 中心のX座標
        int centerY = getHeight() / 2; // 中心のY座標

        int numPoints = values.length; // 頂点の数
        double angleStep = 2 * Math.PI / numPoints; // 各頂点の角度間隔

        // ポリゴンを描画するためのポイント配列
        int[] xPoints = new int[numPoints];
        int[] yPoints = new int[numPoints];

        // 各頂点の位置を計算してポイント配列に格納
        for (int i = 0; i < numPoints; i++) {
            double angle = i * angleStep - Math.PI / 2; // -90度（上方向）から開始
            double radius = (double) values[i] / maxValue * centerY; // 値に応じた半径

            // 極座標を計算して、画面座標に変換
            int x = centerX + (int) (Math.cos(angle) * radius);
            int y = centerY + (int) (Math.sin(angle) * radius);

            xPoints[i] = x;
            yPoints[i] = y;

            // 中心から各頂点に向けて線分を描画
            g2d.setColor(Color.RED); // 線の色を赤に設定
            g2d.drawLine(centerX, centerY, x, y);
        }

        // レーダーチャートの外接円を描画
        g2d.setColor(Color.BLACK); // 外接円の色を黒に設定
        int maxRadius = centerX; // 外接円の半径は中心からの距離
        g2d.drawOval(centerX - maxRadius, centerY - maxRadius, 2 * maxRadius, 2 * maxRadius);

        // ポリゴンを描画（塗りつぶし）
        g2d.setColor(Color.BLUE); // ポリゴンの色を青に設定
        g2d.fillPolygon(xPoints, yPoints);

        // 各頂点にラベルを描画
        g2d.setColor(Color.BLACK); // ラベルの色を黒に設定
        FontMetrics fm = g2d.getFontMetrics();
        for (int i = 0; i < numPoints; i++) {
            double angle = i * angleStep - Math.PI / 2;
            int labelX = centerX + (int) ((Math.cos(angle) * 1.1) * centerX);
            int labelY = centerY + (int) ((Math.sin(angle) * 1.1) * centerY);

            String label = labels[i];
            int labelWidth = fm.stringWidth(label);
            int labelHeight = fm.getHeight();

            g2d.drawString(label, labelX + labelWidth / 2, labelY + labelHeight / 2);
        }
    }

    public static void main(String[] args) {
        int[] values = {60, 80, 50, 70, 90}; // 各頂点の値（0から80までの値）
        String[] labels = {"A", "B", "C", "D", "E"}; // 各頂点のラベル

        JFrame frame = new JFrame("Radar Chart");
        RadarChart radarChart = new RadarChart(values, labels);
        frame.add(radarChart);
        frame.pack();
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
