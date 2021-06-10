package ba.unsa.etf.rpr;

import java.util.ArrayList;

public class Semester {
    public ArrayList<Student> getStudents() {
        return students;
    }

    public ArrayList<Subject> getSubjects() {
        return subjects;
    }

    private ArrayList<Student> students =  new ArrayList<>();
    private ArrayList<Subject> subjects = new ArrayList<>();
    Integer indexCounter = 15000;
    public Semester(ArrayList<Tuple<String, String, Integer, Class>> subjects)throws IllegalArgumentException, NotEnoughPoints{
        if(subjects == null) throw new IllegalArgumentException();
        int sum = 0;
        ArrayList<Subject> newSubjects = new ArrayList<>();
        for(Tuple<String, String, Integer, Class> t : subjects) {
            sum += t.getItem3();
            if(t.getItem4() == Obligatory.class)
                newSubjects.add(new Obligatory(t.getItem1(), t.getItem2(), t.getItem3()));
            else newSubjects.add(new Electoral(t.getItem1(), t.getItem2(), t.getItem3()));
        }
        if(sum < 30) throw new NotEnoughPoints();
        this.subjects = newSubjects;
    }

    public String getElectoralSubjects(){
        String result = new String();
        int i = 1;
        for(Subject s : this.subjects){
            if(s instanceof Electoral){
                result += Integer.toString(i) + ". Subject name: " + s.getSubjectName() + ", Responsible teacher: "
                        + s.getResponsibleTeacher() + ", ECTS: " + Integer.toString(s.getNumberOfECTSPoints()) + "\n";
                i++;
            }
        }
        return result;
    }
    public String getObligatorySubjects(){
        String result = new String();
        int i = 1;
        for(Subject s : this.subjects){
            if(s instanceof Obligatory){
                result += Integer.toString(i) + ". Subject name: " + s.getSubjectName() + ", Responsible teacher: "
                        + s.getResponsibleTeacher() + ", ECTS: " + Integer.toString(s.getNumberOfECTSPoints()) + "\n";
                i++;
            }
        }
        return result;
    }
    public void enrollStudent(Student student, ArrayList<String> electoralSubjects) throws NotEnoughPoints, IllegalArgumentException{
        if(student == null || electoralSubjects == null) throw new IllegalArgumentException();
        boolean ima = false; // check if electorals are correct
        for(String electoral : electoralSubjects) {
            ima = false;
            for (Subject s : this.subjects) {
                if (electoral.equalsIgnoreCase(s.getSubjectName())){
                    ima = true;
                    break;
                }
            }
            if(!ima) throw new IllegalArgumentException();
        }
        for(Subject s : this.subjects){ // enroll student in subjects
            if(s instanceof Obligatory) s.enrollStudent(student);
            else {
                for(String electoral : electoralSubjects)
                    if(electoral.equalsIgnoreCase(s.getSubjectName())){
                        s.enrollStudent(student);
                        break;
                    }
            }
        }
        this.students.add(student); // add student to the semestar
        student.setIndex(this.indexCounter++);
        if(student.getNumberOfECTSPoints() < 30){ // if not enugh ECTS delete student
            student.setIndex(0);
            this.indexCounter--;
            deleteStudent(student.getIndex());

            throw new NotEnoughPoints();
        }
    }
    public void deleteStudent(Integer index){
        for(Subject subject : this.subjects)
            subject.deleteStudent(index);
        for(int i = 0; i < this.students.size(); i++){
            if(this.students.get(i).getIndex().equals(index)){
                this.students.remove(i);
                return;
            }
        }
    }
    public void addSubject(Subject subject){
        for(Subject s : this.subjects)
            if(s.getSubjectName().equalsIgnoreCase(subject.getSubjectName()))
                throw new IllegalArgumentException();
        this.subjects.add(subject);
    }
    public void deleteSubject(String subjectName){
        Subject subject = null;
        for(Subject s : this.subjects)
            if(s.getSubjectName().equalsIgnoreCase(subjectName)){
                subject = s;
                break;
            }
        if(subject == null) throw new IllegalArgumentException();
        this.subjects.remove(subject);
        for(int i = 0; i < students.size(); i++){
            subject.deleteStudent(students.get(i).getIndex());
            if(students.get(i).getNumberOfECTSPoints() < 30){
                deleteStudent(students.get(i).getIndex());
                i--;
            }
        }
    }
}
