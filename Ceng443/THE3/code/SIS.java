import javax.swing.text.html.Option;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.util.stream.Collectors.partitioningBy;

public class SIS {
    private static String fileSep = File.separator;
    private static String lineSep = System.lineSeparator();
    private static String space   = " ";

    private List<Student> studentList = new ArrayList<>();

    public SIS(){ processOptics(); }

    private void processOptics(){
        try{
            //Get all filenames from ./input directory (default location for intelliJ)
            List<Path> fileNames = Files.list(Paths.get("."+fileSep+"input")).collect(Collectors.toList());
            fileNames.stream().forEach(path -> {
                //For each file names under input directory
                List<String> lines;
                String tempSurname;
                String wholeNameSurnameID;
                String yearCourseName;
                String tempTypeOfExam;
                String tempAnswers;
                int tempStudentID;
                int numberOfQuestions;
                double pointOfValue;
                double tempScore;
                Student tempStudent;
                Course tempCourse;
                try {
                    //Get lines from this file
                    lines = Files.lines(path).collect(Collectors.toList());
                    wholeNameSurnameID = lines.get(0);
                    //Split first line according to spaces
                    List<String> namesSurnames = Arrays.asList(wholeNameSurnameID.split(space));
                    //We know that last word is student ID, and second last is surname
                    tempStudentID = Integer.parseInt(namesSurnames.get(namesSurnames.size()-1));
                    tempSurname = namesSurnames.get(namesSurnames.size()-2);
                    //Get student by checking student ID
                    Optional<Student> getStudent = studentList.stream().filter(student -> student.getStudentID() == tempStudentID).findFirst();
                   //If it is present get reference, if not create a new student
                    if(getStudent.isPresent()){
                        tempStudent = getStudent.get();
                    }
                    else{
                        tempStudent = new Student(namesSurnames.stream().limit(namesSurnames.size()-2).toArray(String[]::new),tempSurname,tempStudentID);
                        studentList.add(tempStudent);
                    }
                    //Get second line from the file
                    yearCourseName = lines.get(1);
                    //Split second line according to spaces
                    List<String> splitSecondLine = Arrays.asList(yearCourseName.split(space));
                    //Get second line
                    tempTypeOfExam = lines.get(2);
                    tempAnswers = lines.get(3);
                    numberOfQuestions = tempAnswers.length();
                    pointOfValue = 100.0/numberOfQuestions;
                    //Calculate overall score, strategy is map each char to 0(E,F) or 1 (T), and sum them up
                    tempScore = pointOfValue * tempAnswers.chars().map(givenChar -> {
                        if((char) givenChar == 'T'){
                            return 1;
                        }
                        return 0;
                    }).sum();
                    //Create course based on the values, and add it to the list
                    tempCourse = new Course(Integer.parseInt(splitSecondLine.get(1)),
                                            Integer.parseInt(splitSecondLine.get(0)),
                                            tempTypeOfExam,
                                            Integer.parseInt(splitSecondLine.get(2)),
                                            tempScore
                                            );
                    tempStudent.getTakenCourses().add(tempCourse);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
        }
        catch (Exception e){
            System.out.println(e);
        }

    }

    public double getGrade(int studentID, int courseCode, int year){
        double gradeForStudent = 0;
        //check the student exists
        Optional<Student> givenOptionalStudent = studentList.stream().filter(streamStudent -> streamStudent.getStudentID() == studentID).findFirst();
        if(givenOptionalStudent.isPresent()){

            Optional<Course> midterm1,midterm2,finalOfCourse;
            //Get the student
            Student givenStudent = givenOptionalStudent.get();
            //Get reference of his/her courses
            List<Course> tempCourse = givenStudent.getTakenCourses();
            //Find midterm1 among courses, filter by course year and type
            midterm1 = tempCourse.stream().
                    filter(streamCourse -> streamCourse.getCourseCode() == courseCode).
                    filter(streamCourse -> streamCourse.getYear() == year).
                    filter(streamCourse -> streamCourse.getExamType().equals("Midterm1"))
                    .findFirst();
            //Similarly for midterm 2
            midterm2 = tempCourse.stream().
                    filter(streamCourse -> streamCourse.getCourseCode() == courseCode).
                    filter(streamCourse -> streamCourse.getYear() == year).
                    filter(streamCourse -> streamCourse.getExamType().equals("Midterm2"))
                    .findFirst();
            //lastly for final
            finalOfCourse = tempCourse.stream().
                    filter(streamCourse -> streamCourse.getCourseCode() == courseCode).
                    filter(streamCourse -> streamCourse.getYear() == year).
                    filter(streamCourse -> streamCourse.getExamType().equals("Final"))
                    .findFirst();
            if(midterm1.isPresent() && midterm2.isPresent() && finalOfCourse.isPresent()){
                //If all present update gradeForStudent (return value) according to calculation given in the text
                gradeForStudent = midterm1.get().getGrade()*0.25+midterm2.get().getGrade()*0.25+finalOfCourse.get().getGrade()*0.5;
            }
        }
        return gradeForStudent;
    }

    public void updateExam(int studentID, int courseCode, String examType, double newGrade){
        //filter the given student
        Optional<Student> givenOptionalStudent = studentList.stream().filter(streamStudent -> streamStudent.getStudentID() == studentID).findFirst();
        if(givenOptionalStudent.isPresent()) {
            //If it is present
            Optional<Course> maxOne;
            Student givenStudent = givenOptionalStudent.get();
            List<Course> tempCourse = givenStudent.getTakenCourses();
            //Filter courses and their exams but choose recent's year using max function and find max one according to year
            maxOne = tempCourse.stream().
                    filter(streamCourse -> streamCourse.getCourseCode() == courseCode).
                    filter(streamCourse -> streamCourse.getExamType().equals(examType)).
                    max((course1,course2) -> course1.getYear() - course2.getYear());
            //If present, update its grade
            if(maxOne.isPresent()){
                maxOne.get().setGrade(newGrade);
            }
        }
    }

    public void createTranscript(int studentID){
        //Again first find student
        Optional<Student> givenOptionalStudent = studentList.stream().filter(streamStudent -> streamStudent.getStudentID() == studentID).findFirst();
        //Course Code - Average Weight Mapping
        Map<Integer,Double> cgpaMapping = new HashMap<Integer,Double>();
        //Course Code - Credit Mapping
        Map<Integer,Integer> creditsOfCourses = new HashMap<Integer,Integer>();
        if(givenOptionalStudent.isPresent()){
            Student givenStudent = givenOptionalStudent.get();
            //Group taken courses by year
            Map<Integer,List<Course>> mapOfCourses = givenStudent.getTakenCourses().stream().collect(Collectors.groupingBy(Course::getYear));
            Set<Map.Entry<Integer, List<Course>>> entriesOfMap = mapOfCourses.entrySet();
            //Turn Stream to this mapping, and sort by year
            entriesOfMap.stream().
                    sorted((entryStream1, entryStream2) -> entryStream1.getKey() - entryStream2.getKey()).
                    forEach(givenMapEntry -> {
                        //For each year first print year
                        System.out.println(givenMapEntry.getKey());
                        //get courses that are given by that year
                        List<Course> coursesForGivenYear = givenMapEntry.getValue();
                        //Again group these courses according to course code in order to clusterize Midterm1, Midterm2, and Final
                        Map<Integer,List<Course>> groupedCode = coursesForGivenYear.stream().collect(Collectors.groupingBy(Course::getCourseCode));
                        Set<Map.Entry<Integer, List<Course>>> groupedCodeSet = groupedCode.entrySet();
                        //Again turn this mapping to a stream and sort these values according to course code (Sorted by a year then a course code)
                        groupedCodeSet.stream().
                                sorted((entryStream1, entryStream2) -> entryStream1.getKey() - entryStream2.getKey()).
                                forEach(courseExamList ->{
                                    //Find Midterm1, Midterm2, and Final
                                    Optional<Course> midterm1,midterm2,finalOfCourse;
                                    double gradeForThisCourse = 0;
                                    midterm1 = courseExamList.getValue().stream().
                                            filter(streamCourse -> streamCourse.getExamType().equals("Midterm1"))
                                            .findFirst();
                                    midterm2 = courseExamList.getValue().stream().
                                            filter(streamCourse -> streamCourse.getExamType().equals("Midterm2"))
                                            .findFirst();
                                    finalOfCourse = courseExamList.getValue().stream().
                                            filter(streamCourse -> streamCourse.getExamType().equals("Final"))
                                            .findFirst();
                                    if(midterm1.isPresent() && midterm2.isPresent() && finalOfCourse.isPresent()){
                                        //Calculate grade according to formula
                                        gradeForThisCourse = midterm1.get().getGrade()*0.25+midterm2.get().getGrade()*0.25+finalOfCourse.get().getGrade()*0.5;
                                        //[ASSUMPTION !!!!!!!!] I don't fully understand the forum post, I rounded the letter instead of flooring or ceiling.
                                        int gradeTemp = (int) Math.round(gradeForThisCourse);
                                        //Get course code and credit print course code
                                        int courseCodeOfCurrent = midterm1.get().getCourseCode();
                                        int creditOfCourse = midterm1.get().getCredit();
                                        System.out.printf("%d",courseCodeOfCurrent);
                                        //Save credit of course to a map for further use
                                        creditsOfCourses.put(courseCodeOfCurrent,creditOfCourse);
                                        //Determine letter grade and put it into a map. Since we are traversing min year to max year, using a map will update the weighted average if the course was taken again in the following year
                                        //Ranges are like that in the link
                                        if(gradeTemp <= 100 && gradeTemp >= 90){
                                            System.out.println(" AA");
                                            cgpaMapping.put(courseCodeOfCurrent,4.0*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 89 && gradeTemp >= 85){
                                            System.out.println(" BA");
                                            cgpaMapping.put(courseCodeOfCurrent,3.5*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 84 && gradeTemp >= 80){
                                            System.out.println(" BB");
                                            cgpaMapping.put(courseCodeOfCurrent,3.0*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 79 && gradeTemp >= 75){
                                            System.out.println(" CB");
                                            cgpaMapping.put(courseCodeOfCurrent,2.5*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 74 && gradeTemp >= 70){
                                            System.out.println(" CC");
                                            cgpaMapping.put(courseCodeOfCurrent,2.0*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 69 && gradeTemp >= 65){
                                            System.out.println(" DC");
                                            cgpaMapping.put(courseCodeOfCurrent,1.5*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 64 && gradeTemp >= 60){
                                            System.out.println(" DD");
                                            cgpaMapping.put(courseCodeOfCurrent,1.0*creditOfCourse);
                                        }
                                        else if(gradeTemp <= 59 && gradeTemp >= 50){
                                            System.out.println(" FD");
                                            cgpaMapping.put(courseCodeOfCurrent,0.5*creditOfCourse);
                                        }
                                        else{
                                            System.out.println(" FF");
                                            cgpaMapping.put(courseCodeOfCurrent,0.0*creditOfCourse);
                                        }
                                    }

                                });
                    });
            //Turn these maps to a stream, one is for credit, one is for weighted average
            Set<Map.Entry<Integer,Integer>> creditSet = creditsOfCourses.entrySet();
            Set<Map.Entry<Integer,Double>> cgpaSet = cgpaMapping.entrySet();
            double totalCredit = creditSet.stream().mapToInt(e -> e.getValue()).sum();
            double totalWeight = cgpaSet.stream().mapToDouble(e -> e.getValue()).sum();
            //Calculate CGPA
            System.out.printf("CGPA: %.2f\n",(totalWeight/totalCredit));
        }
    }

    public void findCourse(int courseCode){
        //Combine all students' courses. Filter it to a given course code. Since there are three entries for each course for each student, just take one (in my case it is final) of them to count number of students
        //Group the courses by year (same course different years)
        Map<Integer,List<Course>> tempMap = studentList.stream().
                flatMap(studentStream -> studentStream.getTakenCourses().stream()).
                filter(courseStream -> courseStream.getCourseCode() == courseCode).
                filter(courseStream -> courseStream.getExamType().equals("Final")).
                collect(Collectors.groupingBy(Course::getYear));
        Set<Map.Entry<Integer, List<Course>>> entriesOfMap = tempMap.entrySet();
        //Sort by year, and print their size and year
        entriesOfMap.stream().
                sorted((entryStream1, entryStream2) -> entryStream1.getKey() - entryStream2.getKey()).
                forEach(entryStream -> System.out.println(entryStream.getKey() + " " + entryStream.getValue().size()));
    }

    public void createHistogram(int courseCode, int year){
        //filter the students that take the course in that year
        List<Student> getAllStudent = studentList.stream().
                filter(tempStudent -> tempStudent.getTakenCourses().stream().anyMatch(tempCourse -> tempCourse.getYear() == year && tempCourse.getCourseCode() == courseCode)).
                collect(Collectors.toList());
        //Group them according to their grades, use modulo operation to assign bin. 80-90) will be in 8 so divide by ten will give the result
        Map<Integer,List<Student>> mapOfGrades = getAllStudent.stream().collect(Collectors.groupingBy(tempStudent -> {
            double gradeOfStudent = getGrade(tempStudent.getStudentID(),courseCode,year);
            if(gradeOfStudent == 100){
                //assign bin 9
                return 9;
            }
            else{
                //assign bin grade/10
                int tempValue = (int) gradeOfStudent;
                int returnValue = (int) tempValue/10;
                return returnValue;
            }
        }));
        System.out.println("0-10 "+ (mapOfGrades.containsKey(0) ? mapOfGrades.get(0).size() : 0));
        System.out.println("10-20 "+ (mapOfGrades.containsKey(1) ? mapOfGrades.get(1).size() : 0));
        System.out.println("20-30 "+ (mapOfGrades.containsKey(2) ? mapOfGrades.get(2).size() : 0));
        System.out.println("30-40 "+ (mapOfGrades.containsKey(3) ? mapOfGrades.get(3).size() : 0));
        System.out.println("40-50 "+ (mapOfGrades.containsKey(4) ? mapOfGrades.get(4).size() : 0));
        System.out.println("50-60 "+ (mapOfGrades.containsKey(5) ? mapOfGrades.get(5).size() : 0));
        System.out.println("60-70 "+ (mapOfGrades.containsKey(6) ? mapOfGrades.get(6).size() : 0));
        System.out.println("70-80 "+ (mapOfGrades.containsKey(7) ? mapOfGrades.get(7).size() : 0));
        System.out.println("80-90 "+ (mapOfGrades.containsKey(8) ? mapOfGrades.get(8).size() : 0));
        System.out.println("90-100 "+ (mapOfGrades.containsKey(9) ? mapOfGrades.get(9).size() : 0));
    }
}