import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class rankingData {
    public void ExtractData(String inputFilePath, String outputFilePath, int num) {
        try (BufferedReader br = new BufferedReader(new FileReader(inputFilePath));
             BufferedWriter bw = new BufferedWriter(new FileWriter(outputFilePath))) {

            String line;
            while ((line = br.readLine()) != null) {
                // 各行を"/"で分割
                String[] data = line.split("/");

                // 3つ目と7つ目のデータを抽出
                if (data.length >= num) {
                    String thirdData = data[2];
                    String seventhData = data[num - 1];

                    // 抽出したデータを"/"で結合
                    String result = thirdData + "/" + seventhData;

                    // 結果を新しいファイルに書き込む
                    bw.write(result);
                    bw.newLine();
                }
            }
            System.out.println("データの抽出と書き込みが完了しました。");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        rankingData rankingData = new rankingData();
        rankingData.ExtractData("input.txt", "output.txt", 7);
        Result result = rankingData.sort("output.txt");
        for (int i = 0; i < result.names.length; i++) {
            System.out.println("Name: " + result.names[i] + ", Grip: " + result.grips[i]);
        }
    }
}

class Person {
    public String name;
    public String grip;

    public Person(String name, String grip) {
        this.name = name;
        this.grip = grip;
    }
}

class Result {
    public String[] names;
    public String[] grips;

    public Result(String[] names, String[] grips) {
        this.names = names;
        this.grips = grips;
    }
}
