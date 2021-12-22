package com.event4u.eventsservice.grpc;

import static io.grpc.MethodDescriptor.generateFullMethodName;
import static io.grpc.stub.ClientCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ClientCalls.asyncClientStreamingCall;
import static io.grpc.stub.ClientCalls.asyncServerStreamingCall;
import static io.grpc.stub.ClientCalls.asyncUnaryCall;
import static io.grpc.stub.ClientCalls.blockingServerStreamingCall;
import static io.grpc.stub.ClientCalls.blockingUnaryCall;
import static io.grpc.stub.ClientCalls.futureUnaryCall;
import static io.grpc.stub.ServerCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ServerCalls.asyncClientStreamingCall;
import static io.grpc.stub.ServerCalls.asyncServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnaryCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall;

/**
 */
@javax.annotation.Generated(
    value = "by gRPC proto compiler (version 1.15.0)",
    comments = "Source: event4u.proto")
public final class actionGrpc {

  private actionGrpc() {}

  public static final String SERVICE_NAME = "action";

  // Static method descriptors that strictly reflect the proto.
  private static volatile io.grpc.MethodDescriptor<com.event4u.eventsservice.grpc.Event4U.Request,
      com.event4u.eventsservice.grpc.Event4U.APIResponse> getLogActionMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "logAction",
      requestType = com.event4u.eventsservice.grpc.Event4U.Request.class,
      responseType = com.event4u.eventsservice.grpc.Event4U.APIResponse.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<com.event4u.eventsservice.grpc.Event4U.Request,
      com.event4u.eventsservice.grpc.Event4U.APIResponse> getLogActionMethod() {
    io.grpc.MethodDescriptor<com.event4u.eventsservice.grpc.Event4U.Request, com.event4u.eventsservice.grpc.Event4U.APIResponse> getLogActionMethod;
    if ((getLogActionMethod = actionGrpc.getLogActionMethod) == null) {
      synchronized (actionGrpc.class) {
        if ((getLogActionMethod = actionGrpc.getLogActionMethod) == null) {
          actionGrpc.getLogActionMethod = getLogActionMethod = 
              io.grpc.MethodDescriptor.<com.event4u.eventsservice.grpc.Event4U.Request, com.event4u.eventsservice.grpc.Event4U.APIResponse>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(
                  "action", "logAction"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.event4u.eventsservice.grpc.Event4U.Request.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.event4u.eventsservice.grpc.Event4U.APIResponse.getDefaultInstance()))
                  .setSchemaDescriptor(new actionMethodDescriptorSupplier("logAction"))
                  .build();
          }
        }
     }
     return getLogActionMethod;
  }

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static actionStub newStub(io.grpc.Channel channel) {
    return new actionStub(channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static actionBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    return new actionBlockingStub(channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static actionFutureStub newFutureStub(
      io.grpc.Channel channel) {
    return new actionFutureStub(channel);
  }

  /**
   */
  public static abstract class actionImplBase implements io.grpc.BindableService {

    /**
     */
    public void logAction(com.event4u.eventsservice.grpc.Event4U.Request request,
        io.grpc.stub.StreamObserver<com.event4u.eventsservice.grpc.Event4U.APIResponse> responseObserver) {
      asyncUnimplementedUnaryCall(getLogActionMethod(), responseObserver);
    }

    @java.lang.Override public final io.grpc.ServerServiceDefinition bindService() {
      return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
          .addMethod(
            getLogActionMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                com.event4u.eventsservice.grpc.Event4U.Request,
                com.event4u.eventsservice.grpc.Event4U.APIResponse>(
                  this, METHODID_LOG_ACTION)))
          .build();
    }
  }

  /**
   */
  public static final class actionStub extends io.grpc.stub.AbstractStub<actionStub> {
    private actionStub(io.grpc.Channel channel) {
      super(channel);
    }

    private actionStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected actionStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new actionStub(channel, callOptions);
    }

    /**
     */
    public void logAction(com.event4u.eventsservice.grpc.Event4U.Request request,
        io.grpc.stub.StreamObserver<com.event4u.eventsservice.grpc.Event4U.APIResponse> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getLogActionMethod(), getCallOptions()), request, responseObserver);
    }
  }

  /**
   */
  public static final class actionBlockingStub extends io.grpc.stub.AbstractStub<actionBlockingStub> {
    private actionBlockingStub(io.grpc.Channel channel) {
      super(channel);
    }

    private actionBlockingStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected actionBlockingStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new actionBlockingStub(channel, callOptions);
    }

    /**
     */
    public com.event4u.eventsservice.grpc.Event4U.APIResponse logAction(com.event4u.eventsservice.grpc.Event4U.Request request) {
      return blockingUnaryCall(
          getChannel(), getLogActionMethod(), getCallOptions(), request);
    }
  }

  /**
   */
  public static final class actionFutureStub extends io.grpc.stub.AbstractStub<actionFutureStub> {
    private actionFutureStub(io.grpc.Channel channel) {
      super(channel);
    }

    private actionFutureStub(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected actionFutureStub build(io.grpc.Channel channel,
        io.grpc.CallOptions callOptions) {
      return new actionFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<com.event4u.eventsservice.grpc.Event4U.APIResponse> logAction(
        com.event4u.eventsservice.grpc.Event4U.Request request) {
      return futureUnaryCall(
          getChannel().newCall(getLogActionMethod(), getCallOptions()), request);
    }
  }

  private static final int METHODID_LOG_ACTION = 0;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final actionImplBase serviceImpl;
    private final int methodId;

    MethodHandlers(actionImplBase serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_LOG_ACTION:
          serviceImpl.logAction((com.event4u.eventsservice.grpc.Event4U.Request) request,
              (io.grpc.stub.StreamObserver<com.event4u.eventsservice.grpc.Event4U.APIResponse>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  private static abstract class actionBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
    actionBaseDescriptorSupplier() {}

    @java.lang.Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return com.event4u.eventsservice.grpc.Event4U.getDescriptor();
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
      return getFileDescriptor().findServiceByName("action");
    }
  }

  private static final class actionFileDescriptorSupplier
      extends actionBaseDescriptorSupplier {
    actionFileDescriptorSupplier() {}
  }

  private static final class actionMethodDescriptorSupplier
      extends actionBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
    private final String methodName;

    actionMethodDescriptorSupplier(String methodName) {
      this.methodName = methodName;
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
      return getServiceDescriptor().findMethodByName(methodName);
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (actionGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new actionFileDescriptorSupplier())
              .addMethod(getLogActionMethod())
              .build();
        }
      }
    }
    return result;
  }
}
