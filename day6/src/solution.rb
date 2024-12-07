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
    attr_reader(:guard)

    def initialize(gamemap_string)
      @map = GameMap.new(gamemap_string)
      starting_pos = Pos.new(0, 0)
      @map.map.each do |(pos, symb)|
        next unless symb == :x

        puts "Pos is: #{pos}"
        starting_pos = pos.dup
        break
      end
      @guard = Guard.new(@map.map.clone, starting_pos)
    end

    def next_step
      @guard.walk_forward
    end

    def check_game_state
      @guard.check_next_step
    end
  end

  class Guard
    def initialize(map, starting_pos)
      @map = map
      @starting_pos = starting_pos
      reset_guard
    end

    def reset_guard
      @current_pos = @starting_pos.clone
      @guard_dir = :up
      @steps = 0
    end

    def check_next_step
      (current_x, current_y) = @current_pos.to_a
      next_step = next_pos(current_x, current_y)
      if @map.key?(next_step) == false
        :finished
      else
        @guard_dir = Solution.nextdirection(@guard_dir) if @map[next_step] == :box
        :unfinished
      end
    end

    def walk_forward
      (current_x, current_y) = @current_pos.to_a
      next_pos = next_pos(current_x, current_y)
      @map[next_pos] = :x
      @current_pos = next_pos
      @steps += 1
    end

    def calc_guard_patrol_area
      @map.values.inject(0) { |area, symb| symb == :x ? area + 1 : area }
    end

    def next_pos(current_x, current_y)
      case @guard_dir
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

    private :next_pos
  end

  class GameMap
    attr_reader :map

    def initialize(map_string)
      @map = {}
      maplines = map_string.split("\n")
      (0...maplines.size).zip(maplines).each do |y, line|
        parse_line(line, y)
      end
    end

    def parse_line(line, y_pos)
      (0...line.length).zip(line.split('')).each do |x_pos, c|
        current_pos = Pos.new(x_pos, y_pos)
        @map.merge!({ current_pos => :box }) if c == '#'
        @map.merge!({ current_pos => :dot }) if c == '.'
        @map.merge!({ current_pos => :x }) if c == '^'
      end
    end
  end

  def count_guard_steps(input)
    game = RicochetGuardGame.new(input)
    game.next_step while game.check_game_state == :unfinished
    game.guard.calc_guard_patrol_area
  end

  def find_possible_cycles(input)
    puts input
    42
  end

  module_function :count_guard_steps, :find_possible_cycles
end
