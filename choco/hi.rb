
require 'java'
require 'choco-solver-3.3.1-with-dependencies.jar'
java_import org.chocosolver.solver.Solver
java_import org.chocosolver.solver.variables.VariableFactory
java_import org.chocosolver.solver.constraints.IntConstraintFactory
java_import org.chocosolver.solver.search.strategy.IntStrategyFactory

# must be java 8

solver = Solver.new('my first solver')
x = VariableFactory.bounded('X', 0, 5, solver)
y = VariableFactory.bounded('Y', 0, 5, solver)

solver.post(IntConstraintFactory.arithm(x, "+", y, "<", 5))
solver.post(IntConstraintFactory.arithm(x, ">", 1))
x = VariableFactory.bounded('X', 3, 5, solver)
solver.set(IntStrategyFactory.lexico_LB(x,y))

sol = solver.findSolution
puts sol
puts solver.getSolutionRecorder.getLastSolution


