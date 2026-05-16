namespace Split {

    enum class TimeUnit {
        MICRO_SECONDS,
        MILLI_SECONDS,
        SECONDS
    };

    double convertTime(double , TimeUnit, TimeUnit);
}