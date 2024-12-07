module Solution
  Pos = Struct.new(:x, :y)

  def self.nextdirection(dir)
    nextdirection = {
      up: :right,
      right: :down,
      down: :left,
      left: :up
    }
    nextdirection[dir]
  end

  class RicochetGuardGame
    def initialize(gamemap_string)
      @playerpos = Pos.new(0, 0)
      @gamemap = {}
      @playerdir = :up

      gamelines_arr = gamemap_string.split("\n")
      (0...gamelines_arr.size).zip(gamelines_arr).each do |y, line|
        parse_line(line, y)
      end
    end

    def parse_line(line, y_pos)
      (0...line.length).zip(line.split('')).each do |x_pos, c|
        current_pos = Pos.new(x_pos, y_pos)
        @gamemap.merge!({ current_pos => :box }) if c == '#'
        @gamemap.merge!({ current_pos => :dot }) if c == '.'
        if c == '^'
          @playerpos = current_pos
          @gamemap.merge!({ current_pos => :x })
        end
      end
    end

    def next_step
      (current_x, current_y) = @playerpos.to_a
      next_pos = get_next_pos(current_x, current_y)
      @gamemap[next_pos] = :x
      @playerpos = next_pos
    end

    def get_next_pos(current_x, current_y)
      case @playerdir
      when :up
        Pos.new(current_x, current_y - 1)
      when :down
        Pos.new(current_x, current_y + 1)
      when :left
        Pos.new(current_x - 1, current_y)
      when :right
        Pos.new(current_x + 1, current_y)
      end
    end

    def check_game_state
      (current_x, current_y) = @playerpos.to_a
      next_step = get_next_pos(current_x, current_y)
      if @gamemap.key?(next_step) == false
        :finished
      else
        @playerdir = Solution.nextdirection(@playerdir) if @gamemap[next_step] == :box
        :unfinished
      end
    end

    def game_steps
      count = 0
      @gamemap.each_value { |s| count += 1 if s == :x }
      count
    end
  end

  def count_guard_steps(input)
    game = RicochetGuardGame.new(input)
    game.next_step while game.check_game_state == :unfinished
    game.game_steps
  end

  def find_possible_cycles(input)
    puts input
    42
  end

  module_function :count_guard_steps, :find_possible_cycles
end
