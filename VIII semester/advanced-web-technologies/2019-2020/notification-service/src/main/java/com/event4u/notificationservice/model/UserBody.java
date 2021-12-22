package com.event4u.notificationservice.model;

public class UserBody {

    private Long id;
    private String name;
    private String surname;
    private String username;
    private Long iat;
    private Long exp;


    public UserBody() {
        this(Long.valueOf(1),"" ,"" ,"" ,Long.valueOf(1) ,Long.valueOf(1) );
    }

    public UserBody(Long id, String name, String surname, String username, Long iat, Long exp) {
        this.name = name;
        this.id=id;
        this.surname=surname;
        this.username=username;
        this.iat=iat;
        this.exp=exp;
    }

    public Long getExp() {
        return exp;
    }

    public Long getIat() {
        return iat;
    }

    public Long getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getUsername() {
        return username;
    }
}
