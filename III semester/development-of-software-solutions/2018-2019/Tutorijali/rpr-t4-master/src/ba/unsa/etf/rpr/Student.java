package ba.unsa.etf.rpr;

public class Student {
    private String firstName;
    private String lastName;
    private Integer index;
    private int numberOfECTSPoints = 0;
    public Student(String firstName, String lastName){
        this.firstName = firstName;
        this.lastName = lastName;
    }
    public void setIndex(Integer index){ this.index = index; }
    public Integer getIndex() { return this.index; }
    public void increasePoints(int points){ this.numberOfECTSPoints += points; }
    public int getNumberOfECTSPoints() { return this.numberOfECTSPoints; }
    public String getFirstName() { return this.firstName; }
    public String getLastName() { return this.lastName; }
    public void decreasePoints(int points){
        numberOfECTSPoints -= points;
    }

    @Override
    public String toString() {
        return firstName + " " + lastName + " " + Integer.toString(index) + " " + Integer.toString(numberOfECTSPoints);
    }
}
