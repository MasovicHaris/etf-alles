FROM maven:3.6.3-jdk-11 AS build	
COPY src /home/app/src	
COPY pom.xml /home/app	
WORKDIR /home/app	
RUN ["mvn", "-Dmaven.test.skip=true", "install"]	

FROM openjdk:15-jdk-alpine	
RUN addgroup -S spring && adduser -S spring -G spring	
USER spring:spring	
COPY run.sh eureka.sh	
COPY --from=build /home/app/target/*.jar app.jar	
USER root	
RUN ["chmod", "775", "eureka.sh"]	
ENTRYPOINT ["/eureka.sh"] 