#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

int is_valid(vector<item> items, vector<int> put , int W) {
    int soma = 0;
    for (int i = 0; i < items.size(); i++) {
        soma += items[i].peso * put[i];
    }
    return soma <= W;
}

int fitness(vector<item> items, vector<int> put) {
    int value = 0;
    for (int i = 0; i < items.size(); i++) {
        value += put[i] * items[i].valor;
    }
    return value;
}

void generate_instance(vector<int> &instance) {
    srand(42);  // Seta a semente para geração de números aleatórios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < instance.size(); i++) {
        instance[i] = dis(gen);  // Gera 0 ou 1 aleatoriamente para cada item
    }
}

vector<int> crossover(vector<int> a, vector<int> b) {
    int n = a.size();
    vector<int> output(n);
    for (int i = 0; i < n; i++) {
        output[i] = (i % 2 == 0) ? a[i] : b[i];  // Alterna entre elementos das duas soluções
    }
    return output;
}

vector<int> mutation(vector<int> a) {
    int n = a.size();
    vector<int> output(n);
    int z;
    for (int i = 0; i < n; i++) {
        z = rand() % 100;
        output[i] = (z < 5) ? 1 - a[i] : a[i];  // 5% de chance de mutação (troca 0 por 1 e vice-versa)
    }
    return output;
}

void fill_random(vector<vector<int>> &output) {
    int m = output.size();
    for (int i = 0; i < m; i++) {
        generate_instance(output[i]);
    }
}

vector<int> heuristica(vector<item> items, int W) {
    // Hiperparâmetros
    int n_samples = items.size();
    int max_value = 0;
    int max_iter = 1000;
    int batch_len = 200;
    float epsilon_survivors = 0.2;

    vector<int> output(n_samples);
    vector<int> samples(n_samples);

    int n_survivors = epsilon_survivors * batch_len;
    vector<vector<int>> batch_survivors(n_survivors, vector<int>(n_samples, 0));
    vector<vector<int>> batch(batch_len, vector<int>(n_samples, 0));

    fill_random(batch);  // Inicializa a população

    for (int j = 0; j < max_iter; j++) {
        for (int i = 0; i < batch_len; i++) {
            samples = mutation(batch[i]);
            int value = fitness(items, samples);
            if (is_valid(items, samples, W) && value > max_value){
                max_value = value;
                output = samples;
            }
        }

        // Ordena batch baseado no valor de fitness
        sort(batch.begin(), batch.end(), [&](const vector<int> &a, const vector<int> &b) {
            return fitness(items, a) > fitness(items, b);
        });

        // Copia os melhores indivíduos para os sobreviventes
        for (int i = 0; i < n_survivors; i++) {
            batch_survivors[i] = batch[i];
        }

        // Realiza crossover para criar uma nova população
        for (int i = 0; i < batch_len; i++) {
            batch[i] = crossover(batch_survivors[i % n_survivors], batch_survivors[(i + 1) % n_survivors]);
        }
    }
    
    return output;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string input_filename = argv[1];
    string output_filename = argv[2];

    int N, W;
    ifstream arquivo(input_filename);

    if (!arquivo) {
        cerr << "Error opening input file: " << input_filename << endl;
        return 1;
    }

    arquivo >> N >> W;
    vector<item> items(N);

    for (int i = 0; i < N; i++) {
        arquivo >> items[i].peso >> items[i].valor;
        items[i].id = i;
    }

    arquivo.close();

    vector<int> new_items = heuristica(items, W);

    ofstream output_file(output_filename);

    if (!output_file) {
        cerr << "Error opening output file: " << output_filename << endl;
        return 1;
    }

    for (int i = 0; i < new_items.size(); i++) {
        output_file << new_items[i] << endl;
    }

    for (int i = 0; i < items.size(); i++) {
        if (new_items[i] == 1) {
            output_file << items[i].peso << " " << items[i].valor << endl;
        }
    }

    output_file.close();

    return 0;
}
