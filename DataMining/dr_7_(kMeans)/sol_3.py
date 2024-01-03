import random
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

magic_num = 1000

scaled_max_x = 0
scaled_min_x = 0
scaled_max_y = 0
scaled_min_y = 0

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

def calculate_intra_cluster_distance():
    total_distance = 0

    for centroid in centroids:
        cluster_points = [point for point in points if point.centroid_index == centroids.index(centroid)]
        cluster_distance = sum(compute_squared_distance(point, centroid) for point in cluster_points)
        total_distance += cluster_distance

    return total_distance

def calculate_inter_cluster_distance():
    total_distance = 0

    for i, centroid in enumerate(centroids):
        for j in range(i + 1, len(centroids)):
            inter_distance = compute_squared_distance(centroid, centroids[j])
            total_distance += inter_distance

    return total_distance

def init_random_centroids(K):
    global centroids, scaled_max_x, scaled_min_x, scaled_max_y, scaled_min_y
    
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
    global centroids, indexes_of_points_centroids
    
    indexes_of_points_centroids.clear()
    
    # Pick the first centroid randomly
    point_index = random.randint(0, len(points) - 1)
    indexes_of_points_centroids.add(point_index)

    counter = 1  # Counter for the number of centroids already picked

    while counter < K:
        # Compute distances from each point to all centroids
        distances = []
        for i in range(len(points)):
            min_distance_to_centroids = min(compute_squared_distance(points[i], points[j]) for j in indexes_of_points_centroids)
            distances.append(min_distance_to_centroids)
        
        # Select the point with the farthest distance as the new centroid
        point_index = np.argmax(distances)
        
        indexes_of_points_centroids.add(point_index)
        counter += 1

    centroids = [Point(points[i].x, points[i].y) for i in indexes_of_points_centroids]

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

def clusterize_and_track_best(solution_type):
    global centroids, best_kmeans_assignments, best_kmeans_pp_assignments, best_kmeans_intra, best_kmeans_inter, best_kmeans_pp_intra, best_kmeans_pp_inter
    
    to_continue = True
    is_changed = False

    while to_continue:
        to_continue = False

        for i, point in enumerate(points):
            point.centroid_index = find_nearest_centroid(point)

        for j, centroid in enumerate(centroids):
            is_changed = change_centroid(j)
            to_continue = is_changed or to_continue

    assignments = [point.centroid_index for point in points]

    intra_cluster_distance = calculate_intra_cluster_distance()
    inter_cluster_distance = calculate_inter_cluster_distance()

    if solution_type == "kmeans" and intra_cluster_distance < best_kmeans_intra and inter_cluster_distance > best_kmeans_inter:
        best_kmeans_intra = intra_cluster_distance
        best_kmeans_inter = inter_cluster_distance
        best_kmeans_assignments = assignments.copy()

    if solution_type == "kmeans++" and intra_cluster_distance < best_kmeans_pp_intra and inter_cluster_distance > best_kmeans_pp_inter:
        best_kmeans_pp_intra = intra_cluster_distance
        best_kmeans_pp_inter = inter_cluster_distance
        best_kmeans_pp_assignments = assignments.copy()

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

def draw_k_means(title, subplot_number):
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
    global centroids, best_kmeans_intra, best_kmeans_inter
    
    init_random_centroids(K)
    clusterize_and_track_best("kmeans")

def k_means_plus_plus(K):
    global centroids, indexes_of_points_centroids, point_distances, best_kmeans_pp_intra, best_kmeans_pp_inter
    
    init_centroids_plus_plus(K)
    clusterize_and_track_best("kmeans++")

def main():
    global points, max_x, max_y, min_x, min_y, best_kmeans_assignments, best_kmeans_pp_assignments, best_kmeans_intra, best_kmeans_inter, best_kmeans_pp_intra, best_kmeans_pp_inter

    K = int(input("Enter K: "))
    num_restarts = int(input("Enter the number of restarts: "))
    fname = input("\nEnter file name: ")
      # Read the file and populate the points list
    with open(fname, 'r') as file:
        for line in file:
            x, y = map(float, line.split())
            points.append(Point(x, y))
    
    # Initialize min_x and min_y here
    init_min_max()

    best_kmeans_intra = float('inf')
    best_kmeans_inter = float('-inf')
    best_kmeans_pp_intra = float('inf')
    best_kmeans_pp_inter = float('-inf')

    for restart in range(num_restarts):
        centroids.clear()
        k_means(K)

        centroids.clear()
        k_means_plus_plus(K)

    results = [
        ["K-means", best_kmeans_intra, best_kmeans_inter],
        ["K-means++", best_kmeans_pp_intra, best_kmeans_pp_inter]
    ]
    columns = ["Algorithm", "Intra-cluster Distance", "Inter-cluster Distance"]

    results_df = pd.DataFrame(results, columns=columns)
    print(results_df)

    plt.figure(figsize=(10, 6))
    draw_best_solution("K-means", best_kmeans_assignments, 1)
    centroids.clear()
    draw_best_solution("K-means++", best_kmeans_pp_assignments, 2)

    plt.show()

def draw_best_solution(title, assignments, subplot_number):
    plt.subplot(1, 2, subplot_number)
    plt.subplots_adjust(wspace=0.3) 

    for i, point in enumerate(points):
        x = from_cartesian_to_comp(point.x, True)
        y = from_cartesian_to_comp(point.y, False)
        index = assignments[i]
        
        plt.scatter(x, y, c=get_color(index), marker='o')

    # for i, centroid in enumerate(centroids):
    #     x = from_cartesian_to_comp(centroid.x, True)
    #     y = from_cartesian_to_comp(centroid.y, False)
        
    #     plt.scatter(x, y, c=get_color(i), marker='^', s=100)

    plt.title(title)

if __name__ == "__main__":
    main()