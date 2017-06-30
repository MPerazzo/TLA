import java.util.Scanner;

public class output {

public static void main(String[] args) { 
 Integer v1 = 0; 
 System.out.print("Ingrese un numero valido");
 Scanner _v_v1_s_ = new Scanner(System.in); String _v_v1_s_aux_ = _v_v1_s_.next(); try { v1 = Integer.parseInt(_v_v1_s_aux_); } catch (Exception e) { System.out.println("Compilation Ended"); }
 for ( int iterator = 1 ; iterator < v1 ; iterator++ ) { 
 System.out.print(iterator);
 System.out.print(System.lineSeparator());
 test();
 }
 }

public static void test() { 
 System.out.print("Llamo a la funcion externa");
 System.out.print(System.lineSeparator());
 }

}

