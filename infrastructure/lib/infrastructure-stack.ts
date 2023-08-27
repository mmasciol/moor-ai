import * as cdk from 'aws-cdk-lib';
import { Construct } from 'constructs';
import { CodePipeline, CodePipelineSource, ShellStep} from 'aws-cdk-lib/pipelines';

export class InfrastructureStack extends cdk.Stack {
  constructor(scope: Construct, id: string, props?: cdk.StackProps) {
    super(scope, id, props);

    new CodePipeline(this, 'Pipeline', {
      pipelineName: 'PipelineMoorAI',
      synth: new ShellStep('Synth', {
        input: CodePipelineSource.gitHub('mmasciol/moor-ai', 'main'),
        commands: ['npm ci',
                   'npm run build',
                   'npx cdk synth']
      })
    });
  }
}
