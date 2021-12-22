package com.event4u.systemevents;

import com.event4u.systemevents.grpc.Event4U;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

@Service
public class ActionService {
    @Autowired
    private ActionRepository actionRepository;

    public List<Action> findAll() {
        var it = actionRepository.findAll();
        var actions = new ArrayList<Action>();
        it.forEach(a -> {
            actions.add(a);
        });
        return actions;
    }

    public Long count() {
        return actionRepository.count();
    }

    public Action createAction(String serviceName, Long userId, Event4U.Request.ActionType actionType, String resourceName) {
        Timestamp timestamp = new Timestamp(System.currentTimeMillis());
        return actionRepository.save(new Action(timestamp.toString(), serviceName, userId, actionType, resourceName));
    }
}
