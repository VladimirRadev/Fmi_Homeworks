import random
import matplotlib.pyplot as plt
import numpy as np

magic_num = 1000

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.centroid_index = -1

points = []
centroids = []
indexes_of_points_centroids = set()

point_distances = []
width = 1820
height = 980

def init_x():
    global scaled_max_x, scaled_min_x, max_x, min_x
    
    max_point = max(points, key=lambda p: p.x)
    min_point = min(points, key=lambda p: p.x)

    max_x = max_point.x
    scaled_max_x = max_point.x * magic_num
    min_x = min_point.x
    scaled_min_x = min_point.x * magic_num

def init_y():
    global scaled_max_y, scaled_min_y, max_y, min_y
    
    max_point = max(points, key=lambda p: p.y)
    min_point = min(points, key=lambda p: p.y)

    max_y = max_point.y
    scaled_max_y = max_point.y * magic_num
    min_y = min_point.y
    scaled_min_y = min_point.y * magic_num

def init_min_max():
    init_x()
    init_y()

def compute_squared_distance(a, b):
    return (a.x - b.x) ** 2 + (a.y - b.y) ** 2

def init_random_centroids(K):
    global centroids
    
    random.seed()
    
    for _ in range(K):
        x = (random.random() * magic_num / magic_num) * (scaled_max_x - scaled_min_x) + scaled_min_x
        y = (random.random() * magic_num / magic_num) * (scaled_max_y - scaled_min_y) + scaled_min_y

        centroid = Point(x / magic_num, y / magic_num)
        centroids.append(centroid)

def find_minimal_distance_from_point_to_centroid(point_index):
    min_distance = compute_squared_distance(points[point_index], points[0])
    
    for centroid_index in indexes_of_points_centroids:
        cur_distance = compute_squared_distance(points[point_index], points[centroid_index])

        if cur_distance < min_distance:
            min_distance = cur_distance

    return min_distance

def choose_new_centroid():
    sum_all_point_distances = sum(point_distances)
    val = random.random()
    cur_sum = 0

    for i, distance in enumerate(point_distances):
        cur_sum += distance
        if val < cur_sum / sum_all_point_distances:
            return i

def init_centroids_plus_plus(K):
    global indexes_of_points_centroids, point_distances
    
    indexes_of_points_centroids.clear()
    point_index = random.randint(0, len(points) - 1)
    indexes_of_points_centroids.add(point_index)

    point_distances = [0.0] * len(points)

    counter = 0

    while counter < K - 1:
        for i in range(len(points)):
            if i not in indexes_of_points_centroids:
                point_distances[i] = find_minimal_distance_from_point_to_centroid(i)

        new_centroid_index = choose_new_centroid()

        while new_centroid_index in indexes_of_points_centroids:
            new_centroid_index = choose_new_centroid()

        indexes_of_points_centroids.add(new_centroid_index)
        counter += 1

    for point_index in indexes_of_points_centroids:
        centroid = Point(points[point_index].x, points[point_index].y)
        centroids.append(centroid)

  

def find_nearest_centroid(p):
    min_distance = compute_squared_distance(p, centroids[0])
    nearest_centroid_index = 0
    cur_distance = 0

    for i, centroid in enumerate(centroids):
        cur_distance = compute_squared_distance(p, centroid)

        if cur_distance < min_distance:
            min_distance = cur_distance
            nearest_centroid_index = i

    return nearest_centroid_index

def change_centroid(centroid_index):
    sum_x, sum_y = 0, 0
    counter = 0

    for i, point in enumerate(points):
        if point.centroid_index == centroid_index:
            sum_x += point.x
            sum_y += point.y
            counter += 1

    if counter == 0:
        return False

    new_centroid = Point(sum_x / counter, sum_y / counter)
    old_centroid = centroids[centroid_index]

    if old_centroid.x == new_centroid.x and old_centroid.y == new_centroid.y:
        return False

    centroids[centroid_index] = new_centroid
    del old_centroid

    return True

def clusterize():
    to_continue = True
    is_changed = False

    while to_continue:
        to_continue = False

        for i, point in enumerate(points):
            point.centroid_index = find_nearest_centroid(point)

        for j, centroid in enumerate(centroids):
            is_changed = change_centroid(j)
            to_continue = is_changed or to_continue

def from_cartesian_to_comp(coord, is_x):
    return (coord - min_x) * width / (max_x - min_x) if is_x else (max_y - coord) * height / (max_y - min_y)

def get_color(index):
    colors = [
        'red',
        'blue',
        'green',
        'magenta',
        'yellow',
        'black',
        'cyan',
        'gray',
        'turquoise',
        'purple',
    ]
    
    return colors[index % len(colors)]

def draw_k_means(title,subplot_number):
    plt.subplot(1, 2, subplot_number)
    plt.subplots_adjust(wspace=0.3) 
  

    for i, point in enumerate(points):
        x = from_cartesian_to_comp(point.x, True)
        y = from_cartesian_to_comp(point.y, False)
        index = point.centroid_index
        
        plt.scatter(x, y, c=get_color(index), marker='o')

    for i, centroid in enumerate(centroids):
        x = from_cartesian_to_comp(centroid.x, True)
        y = from_cartesian_to_comp(centroid.y, False)
        
        plt.scatter(x, y, c=get_color(i), marker='^', s=100)

    plt.title(title)
 

def k_means(K):
    global centroids
    
    init_random_centroids(K)
    clusterize()
    draw_k_means("K-means",1)

def k_means_plus_plus(K):
    global centroids, indexes_of_points_centroids, point_distances
    init_centroids_plus_plus(K)
    clusterize()
    draw_k_means("K-means++",2)

def main():
    global points, max_x, max_y, min_x, min_y
    
    K = int(input("Enter K: "))
    fname = input("\nEnter file name: ")

    with open(fname) as file:
        lines = file.readlines()
        for line in lines:
            x, y = map(float, line.split())
            points.append(Point(x, y))

    init_min_max()

    plt.figure(figsize=(10,6))
    k_means(K)
    centroids.clear()
    k_means_plus_plus(K)
    
    plt.show()

if __name__ == "__main__":
    main()