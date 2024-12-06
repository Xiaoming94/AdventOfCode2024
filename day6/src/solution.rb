module Solution
  class RicochetGuardGame
    def initialize(gamemap_string)
      @nextdirection = { up: :right, right: :down, down: :left, left: :up }
      @playerpos = [0, 0]
      @gamemap = {}
      @playerdir = :up

      gamelines_arr = gamemap_string.split("\n")
      (0...gamelines_arr.size).zip(gamelines_arr).each do |y, line|
        parse_line(line, y)
      end
    end

    def parse_line(line, y_pos)
      (0...line.length).zip(line.split('')).each do |x_pos, c|
        current_pos = [x_pos, y_pos]
        @gamemap.merge!({ current_pos => :box }) if c == '#'
        @gamemap.merge!({ current_pos => :dot }) if c == '.'
        if c == '^'
          @playerpos = current_pos
          @gamemap.merge!({ current_pos => :x })
        end
      end
    end

    def next_step
      (current_x, current_y) = @playerpos
      next_pos = get_next_pos(current_x, current_y)
      @gamemap[next_pos] = :x
      @playerpos = next_pos
    end

    def get_next_pos(current_x, current_y)
      case @playerdir
      when :up
        [current_x, current_y - 1]
      when :down
        [current_x, current_y + 1]
      when :left
        [current_x - 1, current_y]
      when :right
        [current_x + 1, current_y]
      end
    end

    def check_next_step
      (current_x, current_y) = @playerpos
      next_step = get_next_pos(current_x, current_y)
      if @gamemap.key?(next_step) == false
        :finished
      else
        @playerdir = @nextdirection[@playerdir] if @gamemap[next_step] == :box
        :unfinished
      end
    end

    def calc_xs
      count = 0
      @gamemap.each_value { |s| count += 1 if s == :x }
      count
    end
  end

  def count_guard_steps(input)
    game = RicochetGuardGame.new(input)
    game.next_step while game.check_next_step == :unfinished
    game.calc_xs
  end

  module_function :count_guard_steps
end
