import java.io.*;

public class ReplaceClass {

    public static void main(String[] args) {
        
        try {
            // Read the contents of GFG.java file into a string
            String fileName = "GFG.java";
            String fileContents = readFile(fileName);
            
            // Replace "class GFG" with "public class GFG"
            String key="public class GFG";
            System.out.println(fileContents.indexOf(key));
            if(fileContents.indexOf(key)==-1){

            	String updatedContents = fileContents.replaceFirst("class GFG", "public class GFG");
	            writeFile(fileName, updatedContents);
            }
            writeFile("input.txt","1\n");
            System.out.println("Done!");
        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static String readFile(String fileName) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line);
            sb.append(System.lineSeparator());
        }
        br.close();
        return sb.toString();
    }

    private static void writeFile(String fileName, String fileContents) throws IOException {
        BufferedWriter bw = new BufferedWriter(new FileWriter(fileName));
        bw.write(fileContents);
        bw.close();
    }
}
