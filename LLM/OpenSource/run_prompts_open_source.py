import os, re, json, time
import torch
from transformers import AutoTokenizer, AutoModelForCausalLM

# ==== Fixed configuration ====
PROMPT_DIR = "Datasets/UnseenCode-FL/Prompt"
OUTPUT_DIR = "Results/SimpleRuns/UnseenCode-FL"

# Use HuggingFace model name here
# Default: DeepSeekCoder-V2-16B
# Replace with one of the following if needed:
#   "deepseek-ai/deepseek-coder-v2-16b-base"
#   "bigcode/starcoder2-15b"
#   "meta-llama/CodeLlama-34b-Instruct-hf"
MODEL = "deepseek-ai/deepseek-coder-v2-16b-base"

SYSTEM_PROMPT = ""   # optional global role, usually empty for HF models
TEMPERATURE = 0.7
MAX_NEW_TOKENS = 2048
N = 1            # number of candidates per file
RETRIES = 3      # retry times if generation fails

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

# ==== Helper functions ====
def natural_key(s: str):
    return [int(t) if t.isdigit() else t for t in re.split(r"(\d+)", s)]

def read_text(path: str) -> str:
    with open(path, "r", encoding="utf-8") as f:
        return f.read()

def write_json(path: str, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        json.dump(obj, f, ensure_ascii=False, indent=2)

# ==== Main logic ====
def main():
    print(f"[INFO] Loading model {MODEL} ...")
    tokenizer = AutoTokenizer.from_pretrained(MODEL)
    model = AutoModelForCausalLM.from_pretrained(
        MODEL,
        device_map="auto",
        torch_dtype=torch.float16
    )

    files = [f for f in os.listdir(PROMPT_DIR)
             if os.path.isfile(os.path.join(PROMPT_DIR, f))
             and f.lower().endswith((".txt", ".md", ".json", ".prompt"))]
    files = sorted(files, key=natural_key)

    print(f"[INFO] Found {len(files)} files in {PROMPT_DIR}")
    for idx, fn in enumerate(files, 1):
        path = os.path.join(PROMPT_DIR, fn)
        prompt = read_text(path)
        print(f"[{idx}/{len(files)}] Sending {fn} ...")

        tries, outputs = 0, None
        while tries < RETRIES:
            try:
                inputs = tokenizer(prompt, return_tensors="pt").to(DEVICE)
                gen_outputs = model.generate(
                    **inputs,
                    max_new_tokens=MAX_NEW_TOKENS,
                    temperature=TEMPERATURE,
                    do_sample=True if TEMPERATURE > 0 else False,
                    num_return_sequences=N
                )
                outputs = [tokenizer.decode(out, skip_special_tokens=True) for out in gen_outputs]
                break
            except Exception as e:
                tries += 1
                print(f"[RETRY] {fn} ({tries}/{RETRIES}) error: {e}")
                time.sleep(2 * tries)

        if outputs is None:
            outputs = [f"[ERROR] Could not get response for {fn}"]

        save_path = os.path.join(OUTPUT_DIR, fn + ".json")
        payload = {
            "file": fn,
            "model": MODEL,
            "responses": outputs,
        }
        write_json(save_path, payload)
        print(f"[OK] Saved -> {save_path}")

if __name__ == "__main__":
    main()
