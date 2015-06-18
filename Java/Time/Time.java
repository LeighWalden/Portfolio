/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package time;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 *
 * @author Leigh
 */
public class Time {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
    Date date = new Date();
      String strDateFormat = "HH:mm:ss a";
      SimpleDateFormat sdf = new SimpleDateFormat(strDateFormat);
      System.out.println(sdf.format(date));
    }
    
}
