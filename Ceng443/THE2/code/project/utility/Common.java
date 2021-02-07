package project.utility;

import project.parts.Arm;
import project.parts.Base;
import project.parts.Part;
import project.parts.logics.*;
import project.parts.payloads.*;
import sun.applet.Main;
import sun.rmi.runtime.Log;

import java.lang.reflect.Field;
import java.util.Random;






public class Common
{
    //Abstract Factory
    public static abstract class AbstractFactory {
        //Produce base code
        public abstract Base getBase(int givenSerialNo);
        //Produce parts code
        public abstract Part getParts(String name);
        public static PartsFactory produceFactory(){
            //Return factory
            return new PartsFactory();
        }
    }
    //Factory
    public static class PartsFactory extends AbstractFactory {
        public Base getBase(int givenSerialNo){
            //return base
            return new Base(givenSerialNo);
        }
        public Part getParts(String name){

            // This function returns a robot part by applying factory and abstract factory patterns
            // In case the function needs to throw an exception, throw this: SmartFactoryException( "Failed: createPart!" )
            Part temp = null;
            //Check their string
            if(name.equals("Arm")){
                temp = new Arm();
                //create new Arm directly
            }
            else if(name.equals("Builder")){
                temp = new Builder();
                //Create builder
            }
            else if(name.equals("Fixer")){
                temp = new Fixer();
                //create fixer
            }
            else if(name.equals("Inspector")){
                temp = new Inspector();
                //create inspector
            }
            else if(name.equals("Supplier")){
                temp = new Supplier();
                //create supplier
            }
            else if(name.equals("Camera")){
                temp = new Camera();
                //create camera
            }
            else if(name.equals("Gripper")){
                temp = new Gripper();
                //create gripper
            }
            else if(name.equals("MaintenanceKit")){
                temp = new MaintenanceKit();
                //create maintenanceKit
            }
            else if(name.equals("Welder")){
                temp = new Welder();
                //create Welder
            }
            else{
                //Not found throw error
                throw new SmartFactoryException( "Failed: createPart!" );
            }
            return temp;
        }
    }

    public static Random random = new Random() ;

    public static synchronized Object get (Object object , String fieldName )
    {
        // This function retrieves (gets) the private field of an object by using reflection
        // In case the function needs to throw an exception, throw this: SmartFactoryException( "Failed: get!" )
        try{
            Field privateFieldOfObject = object.getClass().getDeclaredField(fieldName);
            //Get Field
            privateFieldOfObject.setAccessible(true);
            //Change accessibility of this field (just change this not object or class)
            return privateFieldOfObject.get(object);
            //Return it
        }
        catch (Exception e) {
            throw new SmartFactoryException("Failed: get!");
        }
    }

    public static synchronized void set ( Object object , String fieldName , Object value )
    {
        // This function modifies (sets) the private field of an object by using reflection
        // In case the function needs to throw an exception, throw this: SmartFactoryException( "Failed: set!" )

        try{
            Field privateFieldOfObject = object.getClass().getDeclaredField(fieldName);
            //Get field
            privateFieldOfObject.setAccessible(true);
            //Change accessibility of this field (just change this not object or class)
            privateFieldOfObject.set(object,value);
        }
        catch (Exception e){
            throw new SmartFactoryException( "Failed: set!" );
        }
    }

    //This function randomly gives part name to Supplier in order to create random parts
    public static String getPartName(){
        //This given randomNum is initial random for which part will be produced --> Base or Arm or Payload or Logic, it is for Factory pattern
        int givenRandomNum = random.nextInt(4);
        String returningString;
        if(givenRandomNum == 0){
            //Produce base
            returningString = "Base";
        }
        else if(givenRandomNum == 1){
            //Produce arm
            returningString = "Arm";
        }
        else if(givenRandomNum == 2){
            //We will produce a payload but which one? So get random number again
            givenRandomNum = random.nextInt(4);
            if(givenRandomNum == 0){
                //Produce Camera
                returningString = "Camera";
            }
            else if(givenRandomNum == 1){
                //Produce Gripper
                returningString = "Gripper";
            }
            else if(givenRandomNum == 2){
                //Produce MaintenanceKit
                returningString = "MaintenanceKit";
            }
            else{
                //Produce Welder
                returningString = "Welder";
            }
        }
        else{
            //We will produce a logic but which one? So get random number again
            givenRandomNum = random.nextInt(4);
            if(givenRandomNum == 0){
                //Produce builder
                returningString = "Builder";
            }
            else if(givenRandomNum == 1){
                //Produce fixer
                returningString = "Fixer";
            }
            else if(givenRandomNum == 2){
                //Produce inspector
                returningString = "Inspector";
            }
            else{
                //Produce supplier
                returningString = "Supplier";
            }
        }
        //return the selected string part
        return returningString;
    }

    //This function is for builder to check payload and logic is matched properly
    public static boolean compatibleLogic(Payload givenPayload,Logic givenLogic){
        if(givenPayload instanceof Camera){
            //If payload is Camera, logic should be Inspector
            return (givenLogic instanceof Inspector);
        }
        else if(givenPayload instanceof Gripper){
            //If payload is Gripper, logic should be Supplier
            return (givenLogic instanceof Supplier);
        }
        else if(givenPayload instanceof MaintenanceKit){
            //If payload is MaintenanceKit, logic should be Fixer
            return (givenLogic instanceof Fixer);
        }
        else if(givenPayload instanceof Welder){
            //If payload is Welder, logic should be Builder
            return (givenLogic instanceof Builder);
        }
        else {
            return false;
        }
    }

    //This function is used by fixer to get a new proper payload for broken robot's logic
    public static String getMissingPayload(Logic givenLogic){
        String returningString = null;
        if(givenLogic instanceof Builder){
            //If my logic is builder, payload should be Welder
            returningString = "Welder";
        }
        else if(givenLogic instanceof Fixer){
            //If my logic is fixer, payload should be MaintenanceKit
            returningString = "MaintenanceKit";
        }
        else if(givenLogic instanceof Inspector){
            //If my logic is inspector, payload should be camera
            returningString = "Camera";
        }
        else{
            //Else it is supplier, payload should be Gripper
            returningString = "Gripper";
        }
        return returningString;
    }

    //This function is used by fixer to get a new proper logic for broken robot's payload
    public static String getMissingLogic(Payload givenPayload){
        String returningString = null;
        if(givenPayload instanceof Camera){
            //If my payload is camera, logic should be inspector
            returningString = "Inspector";
        }
        else if(givenPayload instanceof Gripper){
            //If my payload is Gripper, logic should be supplier
            returningString = "Supplier";
        }
        else if(givenPayload instanceof MaintenanceKit){
            //If my payload is MaintenanceKit, logic should be Fixer
            returningString = "Fixer";
        }
        else{
            //Else it is welder, logic should be Builder
            returningString = "Builder";
        }
        return returningString;
    }
}