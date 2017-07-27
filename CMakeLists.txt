cmake_minimum_required(VERSION 3.6)
project(jMetalCpp)
set(CMAKE_CXX_STANDARD 11)

define_property(GLOBAL PROPERTY SOURCE_LIST BRIEF_DOCS "Global list of source code" FULL_DOCS "Global list of source code")
set_property(GLOBAL PROPERTY SOURCE_LIST "")

macro(LIST_APPEND var)
    set_property(GLOBAL APPEND PROPERTY SOURCE_LIST "${var}")
endmacro(LIST_APPEND)

include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/src/core
	${PROJECT_SOURCE_DIR}/src/encodings
	${PROJECT_SOURCE_DIR}/src/encodings/solutionType
	${PROJECT_SOURCE_DIR}/src/encodings/variable
	${PROJECT_SOURCE_DIR}/src/experiments
	${PROJECT_SOURCE_DIR}/src/experiments/main
	${PROJECT_SOURCE_DIR}/src/experiments/settings
	${PROJECT_SOURCE_DIR}/src/experiments/util
	${PROJECT_SOURCE_DIR}/src/main
	${PROJECT_SOURCE_DIR}/src/metaheuristics
	${PROJECT_SOURCE_DIR}/src/metaheuristics/gde3
	${PROJECT_SOURCE_DIR}/src/metaheuristics/mochc
	${PROJECT_SOURCE_DIR}/src/metaheuristics/moead
	${PROJECT_SOURCE_DIR}/src/metaheuristics/nsgaII
	${PROJECT_SOURCE_DIR}/src/metaheuristics/omopso
	${PROJECT_SOURCE_DIR}/src/metaheuristics/paes
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective/cmaes
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective/cmaes/utils
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective/differentialEvolution
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective/geneticAlgorithm
	${PROJECT_SOURCE_DIR}/src/metaheuristics/singleObjective/particleSwarmOptimization
	${PROJECT_SOURCE_DIR}/src/metaheuristics/smpso
	${PROJECT_SOURCE_DIR}/src/metaheuristics/smsemoa
	${PROJECT_SOURCE_DIR}/src/operators
	${PROJECT_SOURCE_DIR}/src/operators/crossover
	${PROJECT_SOURCE_DIR}/src/operators/mutation
	${PROJECT_SOURCE_DIR}/src/operators/selection
	${PROJECT_SOURCE_DIR}/src/problems
	${PROJECT_SOURCE_DIR}/src/problems/DTLZ
	${PROJECT_SOURCE_DIR}/src/problems/LZ09
	${PROJECT_SOURCE_DIR}/src/problems/singleObjective
	${PROJECT_SOURCE_DIR}/src/problems/singleObjective/cec2005Competition
	${PROJECT_SOURCE_DIR}/src/problems/ZDT
	${PROJECT_SOURCE_DIR}/src/qualityIndicator
	${PROJECT_SOURCE_DIR}/src/qualityIndicator/fastHypervolume
	${PROJECT_SOURCE_DIR}/src/qualityIndicator/main
	${PROJECT_SOURCE_DIR}/src/qualityIndicator/util
	${PROJECT_SOURCE_DIR}/src/util
	${PROJECT_SOURCE_DIR}/src/util/archive
	${PROJECT_SOURCE_DIR}/src/util/comparators
	${PROJECT_SOURCE_DIR}/src/util/wrapper
    )
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
get_property(my_source_list GLOBAL PROPERTY SOURCE_LIST)
add_library(${PROJECT_NAME} SHARED ${my_source_list})
