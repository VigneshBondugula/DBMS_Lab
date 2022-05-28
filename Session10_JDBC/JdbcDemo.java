
import java.sql.*;
import java.util.Scanner;


public class JdbcDemo {

   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://localhost/store?useSSL=false";

   //  Database credentials
   static final String USER = "vikky";
   static final String PASS = "vikky123";
   private static Connection conn = null; 

   static void clearScreen() {
      System.out.print("\033[H\033[2J");  
      System.out.flush();
  }
   public static void main(String[] args) {
      JdbcDemo jdbc = new JdbcDemo();
      Scanner scanner = new Scanner(System.in);
      System.out.println("----------------------------------------");
      System.out.println();
      System.out.println("ENTER 0 IF YOU ARE AN ADMIN");
      System.out.println("ENTER 1 IF YOU ARE AN CUSTOMER");
      System.out.println();
      System.out.println("----------------------------------------");
      int user = scanner.nextInt();
      scanner.nextLine();
      if(user == 0){
         while(true){
            System.out.println("Press ENTER to continue...");
            scanner.nextLine();
            clearScreen();
            System.out.println("----------------------------------------");
            System.out.println();
            System.out.println("SELECT 0 TO CONNECT TO DATABASE.");
            System.out.println("SELECT 1 TO ADD A CUSTOMER.");
            System.out.println("SELECT 2 TO ADD A PRODUCT.");
            System.out.println("SELECT 3 TO DELETE A PRODUCT");
            System.out.println("SELECT 4 TO UPDATE PRODUCT STOCK.");
            System.out.println("SELECT 5 TO UPDATE PRODUCT PRICE.");
            System.out.println("SELECT 6 TO VIEW ALL ORDERS.");
            System.out.println("SELECT 7 TO VIEW ALL CUSTOMERS.");
            System.out.println("SELECT 8 TO VIEW ALL PRODUCTS.");
            System.out.println("SELECT 9 TO DISCONNECT.");
            System.out.println();
            System.out.println("----------------------------------------");

            int choice = scanner.nextInt();
            scanner.nextLine();
            if(choice==0){jdbc.start_connection();}
            else if(choice==1){
               System.out.println("ENTER CUSTOMER NAME: ");
               String name = scanner.nextLine();
               System.out.println("ENTER PHONE: ");
               String phone = scanner.nextLine();
               System.out.println("ENTER ADDRESS: ");
               String address = scanner.nextLine();
               jdbc.add_customer(name, phone, address);
            }
            else if(choice==2){
               System.out.println("ENTER PRODUCT NAME: ");
               String name = scanner.nextLine();
               System.out.println("ENTER STOCK: ");
               int stock = scanner.nextInt();
               scanner.nextLine();
               System.out.println("ENTER PRICE: ");
               float price = scanner.nextFloat();
               scanner.nextLine();
               jdbc.add_product(name, stock, price);
            }
            else if(choice==3){
               System.out.println("ENTER PRODUCT ID: ");
               int id = scanner.nextInt();
               scanner.nextLine();
               jdbc.delete_product(id);
            }
            else if(choice==4){
               System.out.println("ENTER STOCK: ");
               int stock = scanner.nextInt();
               scanner.nextLine();
               System.out.println("ENTER PRODUCT ID: ");
               int id = scanner.nextInt();
               scanner.nextLine();
               jdbc.update_product_stock(stock, id);
            }
            else if(choice == 5){
               System.out.println("ENTER PRICE: ");
               float price = scanner.nextFloat();
               scanner.nextLine();
               System.out.println("ENTER PRODUCT ID: ");
               int id = scanner.nextInt();
               scanner.nextLine();
               jdbc.update_product_cost(price, id);
            }
            else if(choice == 6){jdbc.view_orders();}
            else if(choice == 7){jdbc.get_customers_list();;}
            else if(choice == 8){jdbc.get_products_list();}
            else if(choice == 9){
               jdbc.end_connection();
               scanner.close();
               break;
            }
         }    
      }
      else if(user==1){
         while(true){
            System.out.println("Press ENTER to continue...");
            scanner.nextLine();
            clearScreen();
            System.out.println("----------------------------------------");
            System.out.println();
            System.out.println("SELECT 0 TO CONNECT TO DATABASE.");
            System.out.println("SELECT 1 TO PLACE AN ORDER.");
            System.out.println("SELECT 2 TO VIEW ALL PRODUCTS.");
            System.out.println("SELECT 3 TO DISCONNECT.");
            System.out.println();
            System.out.println("----------------------------------------");

            int choice = scanner.nextInt();
            scanner.nextLine();
            if(choice==0){jdbc.start_connection();}
            else if(choice == 1){
               System.out.println("ENTER CUSTOMER ID: ");
               int cust_id = scanner.nextInt();
               scanner.nextLine();
               System.out.println("ENTER PRODUCT ID: ");
               int prod_id = scanner.nextInt();
               scanner.nextLine();
               System.out.println("ENTER QUANTITY: ");
               int quantity = scanner.nextInt();
               scanner.nextLine();
               jdbc.place_order(cust_id, prod_id, quantity);
            }
            else if(choice == 2){jdbc.get_products_list();}
            else if(choice == 3){
               jdbc.end_connection();
               scanner.close();
               break;
            }
         }
      }
   }				

   public void start_connection(){
      try{
         Class.forName(JDBC_DRIVER);
         System.out.println("Connecting to database...");
         conn = DriverManager.getConnection(DB_URL,USER,PASS);
         System.out.println("Database Connected.");
      }
      catch(SQLException se){    	
         se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
   }

   public void get_customers_list(){
      Statement stmt = null;

      try{   
         System.out.println("Retrieving customers...");
         stmt = conn.createStatement();

         String sql;
         sql = "SELECT * from Customer;";
         ResultSet rs = stmt.executeQuery(sql);

         while(rs.next()){
            //Retrieve by column name
            int id = rs.getInt("id");
            String name  = rs.getString("name");
            String phone = rs.getString("phone");
            String address = rs.getString("address");


            //Display values
            System.out.print("Customer ID: " + id);
            System.out.print(", Name: " + name);
            System.out.print(", Phone: " + phone);
            System.out.println(", Address: " + address);
         }

         rs.close();
         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }	

   public void get_products_list(){
      Statement stmt = null;

      try{   
         System.out.println("Retrieving Products...");
         stmt = conn.createStatement();

         String sql;
         sql = "SELECT * from Product;";
         ResultSet rs = stmt.executeQuery(sql);

         while(rs.next()){
            //Retrieve by column name
            int product_id = rs.getInt("product_id");
            String name  = rs.getString("name");
            int stock = rs.getInt("stock");
            float price = rs.getFloat("price");


            //Display values
            System.out.print("Product ID: " + product_id);
            System.out.print(", Name: " + name);
            System.out.print(", Stock Available: " + stock);
            System.out.println(", Price: " + price);
         }

         rs.close();
         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }
   }

   public void add_customer(String name, String phone, String address){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Adding customer...");

         String sql;
         sql = "insert into Customer(name, phone, address) values(?,?,?);";
         stmt = conn.prepareStatement(sql);
         stmt.setString(1,name);
         stmt.setString(2,phone);
         stmt.setString(3,address);

         if(stmt.executeUpdate() == 1){
            System.out.println("Customer Added to the database.");
         }
         else{
            System.out.println("Failed to add the customer.");
         }
         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }

   public void add_product(String name, int stock, float price){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Adding product...");

         String sql;
         sql = "insert into Product(name, stock, price) values(?,?,?);";
         stmt = conn.prepareStatement(sql);
         stmt.setString(1,name);
         stmt.setInt(2,stock);
         stmt.setFloat(3,price);

         if(stmt.executeUpdate() == 1){
            System.out.println("Product Added to the database.");
         }
         else{
            System.out.println("Failed to add the product.");
         }
         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }
   }

   public void delete_product(int id){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Deleting product..");

         String sql;
         sql = "delete from Product where product_id = ?;";
         stmt = conn.prepareStatement(sql);
         stmt.setInt(1, id);

         if(stmt.executeUpdate() == 1){
            System.out.println("Deleted product succesfully.");
         }
         else{
            System.out.println("Failed to delete product.");
         }

         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }

   public void update_product_stock(int stock, int id){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Updating stock..");

         String sql;
         sql = "update Product set stock=? where product_id = ?;";
         stmt = conn.prepareStatement(sql);
         stmt.setInt(1, stock);
         stmt.setInt(2, id);


         if(stmt.executeUpdate() == 1){
            System.out.println("Updated product stock succesfully.");
         }
         else{
            System.out.println("Failed to update product.");
         }

         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }

   public void update_product_cost(float price, int id){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Updating stock..");

         String sql;
         sql = "update Product set price=? where product_id = ?;";
         stmt = conn.prepareStatement(sql);
         stmt.setFloat(1, price);
         stmt.setInt(2, id);


         if(stmt.executeUpdate() == 1){
            System.out.println("Updated product price succesfully.");
         }
         else{
            System.out.println("Failed to update product.");
         }

         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }

   public int place_order(int cust_id, int prod_id, int quantity){
      PreparedStatement stmt = null;

      try{   
         System.out.println("Placing order..");

         String sql;
         sql = "select * from Customer where id = ?;";
         stmt = conn.prepareStatement(sql);
         stmt.setInt(1, cust_id);

         ResultSet rs = stmt.executeQuery();
         if(!rs.next()){
            System.out.println("Customer not found.");
            return -1;
         }
         stmt.close();
         rs.close();
         System.out.println("Customer found.");

         sql = "select * from Product where product_id = ?;";
         stmt = conn.prepareStatement(sql);
         stmt.setInt(1, prod_id);
         ResultSet rs2 = stmt.executeQuery();
         if(!rs2.next()){
            System.out.println("Product not available.");
            return -1;
         }
         int stock = rs2.getInt("stock");
         float price = rs2.getFloat("price");
         float total = quantity * price;
         if(stock < quantity){
            System.out.println("Product not available.");
            return -1;
         }
         else{
            System.out.println("Product found. Placing the order with a total of " + total);
         }
         stmt.close();
         rs2.close();

         sql = "insert into `Order`(`customer_id`, `product_id`, `quantity`, `total_price`, `date`) values(?,?,?,?,?);";
         stmt = conn.prepareStatement(sql);
         stmt.setInt(1,cust_id);
         stmt.setInt(2,prod_id);
         stmt.setInt(3,quantity);
         stmt.setFloat(4,total);
         long millis=System.currentTimeMillis();  
         java.sql.Date date=new java.sql.Date(millis); 
         stmt.setDate(5, date);

         if(stmt.executeUpdate() == 1){
            System.out.println("Order placed succesfully.");
            update_product_stock(stock-quantity, prod_id);
         }
         else{
            System.out.println("Failed to place the order.");
            return -1;
         }
         stmt.close();
         return 0;
      }
      catch(SQLException se){    	
         se.printStackTrace();
         return -1;
      }
      catch(Exception e){        	
         e.printStackTrace();
         return -1;
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }	
   }

   public void view_orders(){
      Statement stmt = null;

      try{   
         System.out.println("Retrieving Orders..");
         stmt = conn.createStatement();

         String sql;
         sql = "SELECT * from `Order`";
         ResultSet rs = stmt.executeQuery(sql);

         while(rs.next()){
            //Retrieve by column name
            int order_id = rs.getInt("order_id");
            int customer_id  = rs.getInt("customer_id");
            int product_id = rs.getInt("product_id");
            int quantity = rs.getInt("quantity");
            float total_price = rs.getFloat("total_price");
            Date date = rs.getDate("date");

            //Display values
            System.out.print("Order_ID: " + order_id);
            System.out.print(", Customer_ID: " + customer_id);
            System.out.print(", Product_ID: " + product_id);
            System.out.print(", Quantity: " + quantity);
            System.out.print(", Total_Price: " + total_price);
            System.out.println(", Date: " + date);
         }

         rs.close();
         stmt.close();
      }
      catch(SQLException se){    	
            se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(stmt!=null)
               stmt.close();
         }
         catch(SQLException se2){
         }				
      }
   }

   public void end_connection(){
      try{
         System.out.println("Disconnecting...");
         conn.close();
      }
      catch(SQLException se){    	
         se.printStackTrace();
      }
      catch(Exception e){        	
         e.printStackTrace();
      }
      finally{				
         try{
            if(conn!=null)
               conn.close();
         }
         catch(SQLException se){
            se.printStackTrace();
         }					
      }	
   }

}					
