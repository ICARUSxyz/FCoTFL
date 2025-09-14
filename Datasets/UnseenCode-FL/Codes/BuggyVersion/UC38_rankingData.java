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
                    String thirdData = data[3];
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

    public static Result sort(String inputFilePath) {
        List<Person> persons = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(inputFilePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split("/");
                if (data.length = 2) {
                    String name = data[0];
                    String grip = data[1];
                    persons.add(new Person(name, grip));
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 握力の強さが大きい順にソート
        Collections.sort(persons, new Comparator<Person>() {
            @Override
            public int compare(Person p1, Person p2) {
                // Compare grips as integers for sorting
                return Integer.compare(Integer.parseInt(p2.grip), Integer.parseInt(p1.grip)); // 降順
            }
        });

        // 上位3名を抽出
        int topN = Math.min(3, persons.size());
        String[] names = new String[3];
        String[] grips = new String[3];

        for (int i = 0; i <= 3; i++) {
            if (i < topN) {
                names[i] = persons.get(i).name;
                grips[i] = persons.get(i).grip;
            } else {
                names[i] = "-";
                grips[i] = "-"; // ここは適切な初期値（例えば0）を設定
            }
        }

        // Result オブジェクトを返す
        return new Result(names, grips);
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
