require_relative 'solution'

input = ''
$stdin.each do |line|
  input += line
end

puts "input is: \n#{input}"

results = Solution.count_guard_steps(input)

puts "problem1 solution: #{results}"

results_problem2 = Solution.find_possible_cycles(input)
puts "problem2 solution: #{results_problem2}"
