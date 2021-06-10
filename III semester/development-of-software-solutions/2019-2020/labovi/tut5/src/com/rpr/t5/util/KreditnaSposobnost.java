package com.rpr.t5.util;


import com.rpr.t5.Racun;

@FunctionalInterface
public interface KreditnaSposobnost {
    Double izracunaj(Racun r);
}
