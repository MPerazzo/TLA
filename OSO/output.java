import java.util.Scanner;

public class output {

public static void main(String[] args) { 
 a();
 System.out.print("Ingrese un primer numero valido");
 System.out.print(System.lineSeparator());
 Integer num1 = 0; 
 Scanner _v_num1_s_ = new Scanner(System.in); String _v_num1_s_aux_ = _v_num1_s_.next(); try { num1 = Integer.parseInt(_v_num1_s_aux_); } catch (Exception e) { System.out.println("Compilation Ended"); return; }
 System.out.print("Ingrese un segundo numero valido");
 System.out.print(System.lineSeparator());
 Integer num2 = 0; 
 Scanner _v_num2_s_ = new Scanner(System.in); String _v_num2_s_aux_ = _v_num2_s_.next(); try { num2 = Integer.parseInt(_v_num2_s_aux_); } catch (Exception e) { System.out.println("Compilation Ended"); return; }
 if ( num2 > num1 ){ 
 for ( int it = 1 ; it < num2 ; it++ ) { 
 b();
 }
 } 
 }

public static void b() { 
 Integer var1 = 5; 
 String hola = "como andan ";
 System.out.print("Hola ");
 System.out.print(hola);
 System.out.print(var1);
 System.out.print(System.lineSeparator());
 }

public static void a() { 
 Integer a = 0; 
 System.out.print("El lenguaje OSO es fabulOSO");
 System.out.print(System.lineSeparator());
 }

}

