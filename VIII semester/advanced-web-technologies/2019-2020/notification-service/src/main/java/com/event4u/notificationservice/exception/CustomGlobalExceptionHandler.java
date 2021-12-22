package com.event4u.notificationservice.exception;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import net.minidev.json.JSONObject;
import net.minidev.json.parser.JSONParser;
import net.minidev.json.parser.ParseException;
import org.springframework.beans.TypeMismatchException;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.BindException;
import org.springframework.validation.FieldError;
import org.springframework.validation.ObjectError;
import org.springframework.web.HttpMediaTypeNotSupportedException;
import org.springframework.web.HttpRequestMethodNotSupportedException;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.MissingServletRequestParameterException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestControllerAdvice;
import org.springframework.web.context.request.WebRequest;
import org.springframework.web.method.annotation.MethodArgumentTypeMismatchException;
import org.springframework.web.multipart.support.MissingServletRequestPartException;
import org.springframework.web.servlet.NoHandlerFoundException;
import org.springframework.web.servlet.mvc.method.annotation.ResponseEntityExceptionHandler;

import javax.servlet.http.HttpServletResponse;
import javax.validation.ConstraintViolation;
import javax.validation.ConstraintViolationException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

@RestControllerAdvice
public class CustomGlobalExceptionHandler extends ResponseEntityExceptionHandler {

    //Not valid //400

    @Override
    protected ResponseEntity<Object> handleMethodArgumentNotValid(final MethodArgumentNotValidException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final List<String> errors = new ArrayList<String>();
        for (final FieldError error : ex.getBindingResult().getFieldErrors()) {
            errors.add(error.getField() + ": " + error.getDefaultMessage());
        }
        for (final ObjectError error : ex.getBindingResult().getGlobalErrors()) {
            errors.add(error.getObjectName() + ": " + error.getDefaultMessage());
        }
        final ApiError apiError = new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), errors);
        return handleExceptionInternal(ex, apiError, headers, apiError.getStatus(), request);
    }


    //Kad ne moze da nadje rezultat u bazi
    @ExceptionHandler({EventNotFoundException.class, UserNotFoundException.class, NotificationNotFoundException.class})
    public void springHandleNotFound(HttpServletResponse response) throws IOException {

        JSONObject Entity2 = new JSONObject();
        Entity2.put("status","Not found");
        Entity2.put("message","Element not found");
        Entity2.put("errors","Element not found");
        PrintWriter out = response.getWriter();
        response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        response.setCharacterEncoding("UTF-8");
        response.setHeader("Content-Type", "application/json");
        out.print(Entity2);
        out.flush();
    }

    //This exception is thrown when fatal binding errors occur.
    @Override
    protected ResponseEntity<Object> handleBindException(final BindException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final List<String> errors = new ArrayList<String>();
        for (final FieldError error : ex.getBindingResult().getFieldErrors()) {
            errors.add(error.getField() + ": " + error.getDefaultMessage());
        }
        for (final ObjectError error : ex.getBindingResult().getGlobalErrors()) {
            errors.add(error.getObjectName() + ": " + error.getDefaultMessage());
        }
        final ApiError apiError = new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), errors);
        return handleExceptionInternal(ex, apiError, headers, apiError.getStatus(), request);
    }

    @Override
    protected ResponseEntity<Object> handleTypeMismatch(final TypeMismatchException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final String error = ex.getValue() + " value for " + ex.getPropertyName() + " should be of type " + ex.getRequiredType();

        headers.setContentType(MediaType.valueOf("application/json"));
        final ApiError apiError = new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), error);
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    //This exception is thrown when when the part of a multipart request not found

    @Override
    protected ResponseEntity<Object> handleMissingServletRequestPart(final MissingServletRequestPartException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        headers.setContentType(MediaType.valueOf("application/json"));
        final String error = ex.getRequestPartName() + " part is missing";
        final ApiError apiError = new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), error);
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }


    //Kad fali parametar
    @Override
    @ResponseBody
    protected ResponseEntity<Object> handleMissingServletRequestParameter(
            MissingServletRequestParameterException ex, HttpHeaders headers,
            HttpStatus status, WebRequest request) {
        String error = ex.getParameterName() + " parameter is missing";
        headers.setContentType(MediaType.valueOf("application/json"));
        ApiError apiError =
                new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), error);

        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

        return new ResponseEntity<Object>(
                jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    //Kad nisu zadovoljena ogranicenja
    @ExceptionHandler({ ConstraintViolationException.class })
    public ResponseEntity<Object> handleConstraintViolation(
            ConstraintViolationException ex, WebRequest request) {
        List<String> errors = new ArrayList<String>();
        for (ConstraintViolation<?> violation : ex.getConstraintViolations()) {
            errors.add(violation.getRootBeanClass().getName() + " " +
                    violation.getPropertyPath() + ": " + violation.getMessage());
        }
        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.valueOf("application/json"));

        ApiError apiError =
                new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), errors);
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    //Kad argument metode nije predviđenog tipa
    @ExceptionHandler({ MethodArgumentTypeMismatchException.class })
    public ResponseEntity<Object> handleMethodArgumentTypeMismatch(
            MethodArgumentTypeMismatchException ex, WebRequest request) {
        String error =
                ex.getName() + " should be of type " + ex.getRequiredType().getName();

        HttpHeaders headers = new HttpHeaders();
        headers.setContentType(MediaType.valueOf("application/json"));
        ApiError apiError =
                new ApiError(HttpStatus.BAD_REQUEST, ex.getLocalizedMessage(), error);
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    // 404

    @Override
    protected ResponseEntity<Object> handleNoHandlerFoundException(final NoHandlerFoundException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final String error = "No handler found for " + ex.getHttpMethod() + " " + ex.getRequestURL();

        headers.setContentType(MediaType.valueOf("application/json"));
        final ApiError apiError = new ApiError(HttpStatus.NOT_FOUND, ex.getLocalizedMessage(), error);
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    // 405

    @Override
    protected ResponseEntity<Object> handleHttpRequestMethodNotSupported(final HttpRequestMethodNotSupportedException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final StringBuilder builder = new StringBuilder();
        builder.append(ex.getMethod());
        builder.append(" method is not supported for this request. Supported methods are ");
        ex.getSupportedHttpMethods().forEach(t -> builder.append(t + " "));

        headers.setContentType(MediaType.valueOf("application/json"));
        final ApiError apiError = new ApiError(HttpStatus.METHOD_NOT_ALLOWED, ex.getLocalizedMessage(), builder.toString());
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    // 415

    @Override
    protected ResponseEntity<Object> handleHttpMediaTypeNotSupported(final HttpMediaTypeNotSupportedException ex, final HttpHeaders headers, final HttpStatus status, final WebRequest request) {
        logger.info(ex.getClass().getName());
        //
        final StringBuilder builder = new StringBuilder();
        builder.append(ex.getContentType());
        builder.append(" media type is not supported. Supported media types are ");
        ex.getSupportedMediaTypes().forEach(t -> builder.append(t + " "));

        headers.setContentType(MediaType.valueOf("application/json"));
        final ApiError apiError = new ApiError(HttpStatus.UNSUPPORTED_MEDIA_TYPE, ex.getLocalizedMessage(), builder.substring(0, builder.length() - 2));
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }


    //Default handler
    @ExceptionHandler({ Exception.class })
    public ResponseEntity<Object> handleAll(Exception ex, WebRequest request) {
        ApiError apiError = new ApiError(
                HttpStatus.INTERNAL_SERVER_ERROR, ex.getLocalizedMessage(), "Error occurred");
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.valueOf("application/json"));
            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }

    @ExceptionHandler({ NullPointerException.class, IllegalArgumentException.class, IllegalStateException.class })
    /*500*/public ResponseEntity<Object> handleInternal(final RuntimeException ex, final WebRequest request) {
        ApiError apiError = new ApiError(
                HttpStatus.INTERNAL_SERVER_ERROR, ex.getLocalizedMessage(), "Other exception");
        try {
            String jsonObject = new ObjectMapper().writeValueAsString(apiError);

            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.valueOf("application/json"));
            return new ResponseEntity<Object>(
                    jsonObject, headers, apiError.getStatus());
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return null;
        }
    }
}
