// 14 p2
// This was trying to be clever by only iterating over events(point in time
// where deers change status). However, this ended by being a verbose
// implementation for no reason and many edge cases
int p2(const std::vector<std::string> &in, const int duration) {
  const auto deers = parse(in);

  std::priority_queue<int> events{};
  for (const auto &d : deers) {
    for (int i{1}; i * (d.fly + d.rest) < duration; ++i) {
      events.emplace(-(((i - 1) * (d.fly + d.rest)) + d.fly));
      events.emplace(-(i * (d.fly + d.rest)));
    }
  }
  events.emplace(-duration);

  int ts{0}, ds{0}, te{0}, de{0};
  std::vector<int> points(deers.size(), 0);
  while (!events.empty()) {
    te = -(events.top());
    events.pop();
    // int best{std::numeric_limits<int>::min()};
    std::cout << "ts: " << ts << " "
              << "te: " << te << std::endl;
    for (const auto &d : deers) {
      de = std::max(de, distance(d, te));
    }
    std::cout << "best: " << de << std::endl;
    for (size_t i = 0; i < deers.size(); ++i) {
      const auto &d = deers[i];
      if (de == distance(d, te)) {
        int diff = ds - distance(d, ts);
        int gap = (diff + d.fly - 1) / d.fly;
        points[i] += (te - ts - gap);
        std::cout << "i: " << i << " "
                  << "gap: " << gap << " " << points[i] << std::endl;
      }
    }
    ts = te;
    ds = de;
  }
  std::cout << points[0] << std::endl;
  return *std::max_element(points.begin(), points.end());
}