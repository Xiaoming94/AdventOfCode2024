module Solution
  def my_const_value()
    puts "Hello"
    42
  end

  module_function :my_const_value
end
