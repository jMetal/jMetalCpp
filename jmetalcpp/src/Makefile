MAKE = make
SUBDIRS = core util util/archive util/comparators util/wrapper operators/crossover \
	operators/mutation operators/selection encodings/solutionType encodings/variable metaheuristics \
	problems experiments/settings experiments/util experiments qualityIndicator qualityIndicator/util
LIBRARIES = core/libcore.a util/libarchive.a util/libutil.a util/libwrapper.a \
	problems/libproblems.a util/comparators/libcomparators.a operators/crossover/libcrossover.a \
	operators/mutation/libmutation.a operators/selection/libselection.a \
	encodings/solutionType/libsolutionType.a encodings/variable/libvariable.a \
	metaheuristics/libmetaheuristics.a qualityIndicator/libqualityIndicator.a \
	qualityIndicator/util/libqualityIndicatorUtil.a
	
all:
	for subdir in `echo "$(SUBDIRS)"`; do ($(MAKE) -C $$subdir $@) ; done
	for subdir in `echo "$(SUBDIRS)"`; do (ar -r libjmetal.a $$subdir/*.o) ; done
	ranlib libjmetal.a
	make -C main
	make -C qualityIndicator/main

clean:
	for subdir in `echo "$(SUBDIRS)"`; do ($(MAKE) -C $$subdir $@) ; done
	make -C main clean
	make -C qualityIndicator/main clean
	rm -f libjmetal.a
