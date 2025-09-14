import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class DataUse {
    
    public static String getNameForID(String id, String csvFilePath) {
        String name = null;
        
        try (BufferedReader br = new BufferedReader(new FileReader(csvFilePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split("/");
                if (data.length >= 3 && data[0].equals(id)) {
                    name = data[2];
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return name;
    }

    public static String getIDForName(String name, String csvFilePath) {
        String id = null;
        
        try (BufferedReader br = new BufferedReader(new FileReader(csvFilePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] data = line.split("/");
                System.out.println("DataUse: " + data[2]);
                if (data.length >= 3 && data[2].equals(name)) {
                    id = data[0];
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        return id;
    }

    public static int[] readFitnessData(String id, String filename) {
        
        int[] data = new  int[5];

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split("/");
                String customerId = parts[0];

                if (customerId.equals(id)) {
                    // 該当する顧客の体力測定値を配列に格納
                    //int[] data = new int[5];
                    for (int i = 0; i < 5; i++) {
                        data[i] = Integer.parseInt(parts[6 + i]); // 体力測定値の部分はインデックス6から始まる
                    }
                    break; // 見つかったらループを抜ける
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return data;
    }
}
