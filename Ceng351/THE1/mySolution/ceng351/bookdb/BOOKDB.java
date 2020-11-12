/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ceng.ceng351.bookdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.Statement;

/**
 *
 * @author furkan
 */
public class BOOKDB implements IBOOKDB {
    private static String user = "2237436";//"pa1_user";  
    private static String password = "bd1d2712"; //"123456";
    private static String host = "144.122.71.65"; //"localhost";
    private static String database = "db2237436";//"pa1_recitation";
    private static int port = 8084; // 3306;
     
    private Connection con;

    public BOOKDB() {
        // TODO Auto-generated constructor stub
    }
    
    @Override
    public void initialize(){
        String url = "jdbc:mysql://" + this.host + ":" + this.port + "/" + this.database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            this.con =  DriverManager.getConnection(url, this.user, this.password);
        } catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        } 
    }
    
    
    //HEPSİNİ AYRI TRY CATCHLERDE YAP
    @Override
    public int createTables(){
        int result;
        int numberofTablesInserted = 0;
        //author(author id:int, author name:varchar(60))
        String queryCreateAuthorTable = "create table author(author_id int, author_name varchar(60), primary key (author_id))";
      
        //publisher(publisher id:int, publisher name:varchar(50))
        String queryCreatePublisherTable = "create table publisher(publisher_id int,"+
                                               "publisher_name varchar(50),primary key (publisher_id))";
      
        /*book(isbn:char(13), book name:varchar(120), publisher id:int, first publish year:char(4), page count:int, category:varchar(25),
        rating:float) REFERENCES publisher(publisher id)*/
        String queryCreateBookTable = "create table book(isbn char(13),book_name varchar(120),publisher_id int,"+
                                      "first_publish_year char(4), page_count int, category varchar(25),"+
                                      "rating float, primary key (isbn), foreign key (publisher_id) references publisher(publisher_id))";
        
        
        //author of (isbn:char(13),author id:int) REFERENCES book(isbn) author(author id)
        String queryCreateAuthor_ofTable = "create table author_of(isbn char(13),author_id int,primary key (isbn,author_id),"+
                "foreign key (isbn) references book(isbn),foreign key (author_id) references author(author_id))";
      
        //phw1(isbn:char(13), book name:varchar(120), rating:float)
        String queryCreatePhw1Table = "create table phw1(isbn char(13),book_name varchar(120),rating float,primary key (isbn))";

        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryCreateAuthorTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e){
            e.printStackTrace();
        }
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryCreatePublisherTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e){
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryCreateBookTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e){
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryCreateAuthor_ofTable);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e){
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryCreatePhw1Table);
            numberofTablesInserted++;
            statement.close();
        } catch (SQLException e){
            e.printStackTrace();
        }
        
        
        return numberofTablesInserted;
    }
    
    @Override
    public int dropTables(){
        int result;
        int numberofTablesDropped = 0;

        
        String queryDropAuthor_ofTable = "drop table author_of";
        String queryDropBookTable = "drop table book";
        String queryDropAuthorTable = "drop table author";
        String queryDropPublisherTable = "drop table publisher";
        String queryDropPhw1Table = "drop table phw1";
        


        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryDropAuthor_ofTable);
            numberofTablesDropped++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryDropBookTable);
            numberofTablesDropped++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryDropAuthorTable);
            numberofTablesDropped++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryDropPublisherTable);
            numberofTablesDropped++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(queryDropPhw1Table);
            numberofTablesDropped++;
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return numberofTablesDropped;
    }
    
    @Override
    public int insertAuthor(Author[] authors){
        int numberOfInsertions = 0;
        int result;
        for(int i=0;i<authors.length;i++){
            try{
                        String query = "insert into author(author_id,author_name) values("+authors[i].getAuthor_id()+",?)"; 
                        PreparedStatement st = this.con.prepareStatement(query);
                        st.setString(1,authors[i].getAuthor_name());
                        result = st.executeUpdate();
                        numberOfInsertions++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return numberOfInsertions;
    }
    
    @Override
    public int insertBook(Book[] books){
        int numberOfInsertions = 0;
        int result;
        for(int i=0;i<books.length;i++){
            try{
                        String query = "insert into book(isbn,book_name,publisher_id,first_publish_year,page_count,category,rating)"+
                                       " values(?,?, "
                                           + books[i].getPublisher_id() + ",?, "
                                           + books[i].getPage_count()+ ",?, " 
                                           + books[i].getRating() + ")";
                        PreparedStatement st = this.con.prepareStatement(query);
                        st.setString(1,books[i].getIsbn());
                        st.setString(2,books[i].getBook_name());
                        st.setString(3,books[i].getFirst_publish_year());
                        st.setString(4,books[i].getCategory());
                        result = st.executeUpdate();
                        numberOfInsertions++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return numberOfInsertions;
    }
    
    @Override
    public int insertPublisher(Publisher[] publishers){
        int numberOfInsertions = 0;
        int result;
        for(int i=0;i<publishers.length;i++){
            try{
                        String query = "insert into publisher(publisher_id,publisher_name)"+
                                       " values("+ publishers[i].getPublisher_id()+ ", ?)";
                        PreparedStatement st = this.con.prepareStatement(query);
                        st.setString(1,publishers[i].getPublisher_name());
                        result = st.executeUpdate();
                        numberOfInsertions++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return numberOfInsertions;
    }
    
    @Override
    public int insertAuthor_of(Author_of[] author_ofs){
        int numberOfInsertions = 0;
        int result;
        for(int i=0;i<author_ofs.length;i++){
            try{
                        String query = "insert into author_of(isbn,author_id)"+
                                       " values(?,"+ author_ofs[i].getAuthor_id()+ ")";
                        PreparedStatement st = this.con.prepareStatement(query);
                        st.setString(1,author_ofs[i].getIsbn());
                        result = st.executeUpdate();
                        numberOfInsertions++;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
        return numberOfInsertions;
    }
    
    @Override
    public QueryResult.ResultQ1[] functionQ1(){
        ResultSet rs;
        QueryResult.ResultQ1 returnValue[] = null;
        String query = "SELECT DISTINCT B.isbn,B.first_publish_year,B.page_count,P.publisher_name\n" +
                        "FROM publisher P, book B\n" +
                        "WHERE B.publisher_id = P.publisher_id AND B.page_count = (SELECT MAX(B2.page_count) FROM book B2) ORDER BY B.isbn";
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ1[rows];
                while (rs.next()) {
                String isbn = rs.getString("isbn");
                String first_publish_year = rs.getString("first_publish_year");
                int page_count = rs.getInt("page_count");
                String publisher_name = rs.getString("publisher_name");
                QueryResult.ResultQ1 temp = new QueryResult.ResultQ1(isbn,first_publish_year,page_count,publisher_name);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ2[] functionQ2(int author_id1, int author_id2){
        ResultSet rs;
        QueryResult.ResultQ2 returnValue[] = null;
        String query =  "SELECT DISTINCT Temp.pid, AVG(B.page_count) as avgcount FROM "
                + "(SELECT DISTINCT B.publisher_id as pid FROM author_of Ao,book B "
                + "WHERE B.isbn = Ao.isbn AND Ao.author_id = "+ author_id1
                + " AND EXISTS (SELECT * FROM author_of ao2 WHERE ao2.isbn = Ao.isbn AND ao2.author_id = "+ author_id2 +")) AS Temp, "
                + "book B WHERE B.publisher_id = Temp.pid GROUP BY Temp.pid ORDER BY Temp.pid";
        try{
            PreparedStatement st = this.con.prepareStatement(query);
            rs = st.executeQuery(query);
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ2[rows];
                while (rs.next()) {
                int publisher_id = rs.getInt("pid");
                double avgcount = rs.getDouble("avgcount");
                QueryResult.ResultQ2 temp = new QueryResult.ResultQ2(publisher_id,avgcount);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ3[] functionQ3(String author_name){
        ResultSet rs;
        QueryResult.ResultQ3 returnValue[] = null;
        String query =  "SELECT DISTINCT B.book_name,B.first_publish_year,B.category FROM book B, author_of Ao, author A WHERE " +
                        "A.author_id = Ao.author_id AND Ao.isbn = B.isbn AND A.author_name = ? "
                        +"AND B.first_publish_year = (SELECT MIN(B2.first_publish_year) FROM book B2, author_of Ao2, author A2 WHERE " +
                    "A2.author_id = Ao2.author_id AND Ao2.isbn = B2.isbn AND A2.author_name = ?) ORDER BY B.book_name,B.category,B.first_publish_year";
        try{
            PreparedStatement st = this.con.prepareStatement(query);
            st.setString(1,author_name);
            st.setString(2,author_name);
            rs = st.executeQuery();
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ3[rows];
                while (rs.next()) {
                String book_name = rs.getString("book_name");
                String first_publish_year = rs.getString("first_publish_year");
                String category = rs.getString("category");
                QueryResult.ResultQ3 temp = new QueryResult.ResultQ3(book_name,category,first_publish_year);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ4[] functionQ4(){
        ResultSet rs;
        QueryResult.ResultQ4 returnValue[] = null;
        String query = "SELECT DISTINCT B.publisher_id, B.category FROM book B, publisher P "
                + "WHERE B.publisher_id = P.publisher_id "
                + "AND P.publisher_name LIKE '%_% %_% %_%' AND (SELECT COUNT(*) FROM book B2 WHERE B2.publisher_id = B.publisher_id)>=3 "
                + "AND (SELECT AVG(B2.rating) FROM book B2 WHERE B2.publisher_id = B.publisher_id)> 3 ORDER BY B.publisher_id,B.category";
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ4[rows];
                while (rs.next()) {
                int publisher_id = rs.getInt("publisher_id");
                String category = rs.getString("category");
                QueryResult.ResultQ4 temp = new QueryResult.ResultQ4(publisher_id,category);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ5[] functionQ5(int author_id){
        ResultSet rs;
        QueryResult.ResultQ5 returnValue[] = null;
        String query = "SELECT A.author_id,A.author_name FROM author A WHERE NOT EXISTS "
                + "(SELECT B1.publisher_id FROM book B1, author_of Ao1 "
                + "WHERE Ao1.isbn = B1.isbn AND Ao1.author_id = "+author_id+" AND NOT EXISTS (SELECT B2.publisher_id FROM book B2, author_of Ao2 "
                + "WHERE Ao2.isbn = B2.isbn AND Ao2.author_id = A.author_id AND B1.publisher_id = B2.publisher_id)) ORDER BY A.author_id";
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(query);
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ5[rows];
                while (rs.next()) {
                int getauthor_id = rs.getInt("author_id");
                String author_name = rs.getString("author_name");
                QueryResult.ResultQ5 temp = new QueryResult.ResultQ5(getauthor_id,author_name);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ6[] functionQ6(){
        ResultSet rs;
        QueryResult.ResultQ6 returnValue[] = null;
        String query = "SELECT ao3.author_id, B3.isbn FROM book B3, "
                + "(SELECT DISTINCT ao2.author_id as authors FROM author_of ao2, book B2 WHERE ao2.isbn = B2.isbn AND B2.publisher_id "
                + "IN (SELECT B1.publisher_id FROM book B1, author_of ao WHERE ao.isbn = B1.isbn GROUP BY B1.publisher_id "
                + "HAVING COUNT(DISTINCT author_id) = 1)) as Temp, author_of ao3 "
                + "WHERE ao3.isbn = B3.isbn AND Temp.authors = ao3.author_id ORDER BY ao3.author_id,B3.isbn";
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(query);    
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ6[rows];
                while (rs.next()) {
                int author_id = rs.getInt("author_id");
                String isbn = rs.getString("isbn");
                QueryResult.ResultQ6 temp = new QueryResult.ResultQ6(author_id,isbn);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public QueryResult.ResultQ7[] functionQ7(double rating){
        ResultSet rs;
        QueryResult.ResultQ7 returnValue[] = null;
        String query = "SELECT DISTINCT P.publisher_id, P.publisher_name FROM publisher P, book B "
                + "WHERE B.publisher_id = P.publisher_id AND B.category = 'Roman' GROUP BY P.publisher_id,P.publisher_name "
                +       "HAVING COUNT(*) >= 2 AND "
                +       "(SELECT AVG(B2.rating) FROM book B2 WHERE B2.publisher_id = P.publisher_id) > "+ rating +" ORDER BY P.publisher_id";
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(query);    
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ7[rows];
                while (rs.next()) {
                int getpublisher_id = rs.getInt("publisher_id");
                String getpublisher_name = rs.getString("publisher_name");
                QueryResult.ResultQ7 temp = new QueryResult.ResultQ7(getpublisher_id,getpublisher_name);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    
    @Override
    public QueryResult.ResultQ8[] functionQ8(){
        ResultSet rs;
        QueryResult.ResultQ8 returnValue[] = null;
        int result;
        String addQuery = "INSERT INTO phw1(isbn,book_name,rating) "
                        + "SELECT DISTINCT B1.isbn,B1.book_name,B1.rating FROM book B1 WHERE B1.book_name IN "
                        + "(SELECT B2.book_name FROM book B2 GROUP BY B2.book_name HAVING COUNT(*) >=2) "
                        + "AND B1.rating = (Select MIN(B3.rating) FROM book B3 WHERE B3.book_name = B1.book_name)";
        String getQuery = "SELECT Ph.isbn, Ph.book_name, Ph.rating FROM phw1 Ph ORDER BY Ph.isbn";
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(addQuery);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(getQuery);    
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                int i=0;
                returnValue = new QueryResult.ResultQ8[rows];
                while (rs.next()) {
                String isbn = rs.getString("isbn");
                String book_name = rs.getString("book_name");
                double rating = rs.getDouble("rating");
                QueryResult.ResultQ8 temp = new QueryResult.ResultQ8(isbn,book_name,rating);
                returnValue[i++] = temp;
                }
            }
            
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnValue;
    }
    
    @Override
    public double functionQ9(String keyword){
        ResultSet rs;
        double returnDouble = 0;
        int result;
        String updateQuery = "Update book B SET B.rating =  B.rating +1 WHERE B.book_name LIKE ? AND B.rating<=4";
        String getQuery = "SELECT SUM(B.rating) AS newRating From book B";
        try {
            PreparedStatement st = this.con.prepareStatement(updateQuery);
            st.setString(1,"%" +keyword+"%");
            result = st.executeUpdate();
            st.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(getQuery);    
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                while (rs.next()) {
                 returnDouble = rs.getDouble("newRating");
                }
            }
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnDouble;
    }
    
    @Override
    public int function10(){
        ResultSet rs;
        int returnInt = 0;
        int result;
        String updateQuery = "DELETE FROM publisher P WHERE P.publisher_id NOT IN (SELECT DISTINCT B.publisher_id FROM book B)";
        String getQuery = "SELECT COUNT(*) as count FROM publisher P";
        try {
            Statement statement = this.con.createStatement();
            result = statement.executeUpdate(updateQuery);
            statement.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        try{
            Statement st = this.con.createStatement();
            rs = st.executeQuery(getQuery);    
            int rows = 0;
            rs.last();
            rows = rs.getRow();
            rs.beforeFirst();
            if(rows != 0){
                while (rs.next()) {
                 returnInt = rs.getInt("count");
                }
            }
        } catch(SQLException e){
            e.printStackTrace();
        }
        return returnInt;
    }
    
}
