from flask import Flask, jsonify
import subprocess
import json

app = Flask(__name__)

@app.route('/gpu-stats', methods=['GET'])
def get_gpu_stats():
    process = subprocess.Popen(["./GPU_Interactor"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    if process.returncode != 0:
        return jsonify({"error": "Failed to retrieve GPU stats"}), 500
    
    output = stdout.decode('utf-8')
    gpu_stats = parse_gpu_output(output)

    return jsonify(gpu_stats)

def parse_gpu_output(output):
    stats = {}
    lines = output.splitlines()
    for line in lines:
        if 'GPU Temperature' in line:
            stats['temperature'] = int(line.split(':')[1].strip().replace('C', ''))
        elif 'GPU Utilization' in line:
            stats['utilization'] = int(line.split(':')[1].strip().replace('%', ''))
        elif 'GPU Memory Used' in line:
            stats['memory_used'] = int(line.split(':')[1].strip().replace('MB', ''))
        elif 'GPU Memory Free' in line:
            stats['memory_free'] = int(line.split(':')[1].strip().replace('MB', ''))
    return stats

if __name__ == '__main__':
    app.run(debug=True)
